#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cassert>
#include <omp.h>

// ... [Include all your existing functions: nextRand48, prevRand48, mapToChar, etc.] ...

// Define pair structures
struct ForwardPair {
    uint64_t a4;
    uint64_t a0;
};

struct BackwardPair {
    uint64_t a4;
    uint64_t a8;
};

// Function to compute M^n mod 2^48
uint64_t powM(uint64_t M, int n) {
    uint64_t result = 1;
    uint64_t base = M;
    while (n > 0) {
        if (n & 1) {
            __uint128_t temp = (__uint128_t(result) * base) & ((1ULL << 48) - 1);
            result = (uint64_t)temp;
        }
        __uint128_t temp = (__uint128_t(base) * base) & ((1ULL << 48) - 1);
        base = (uint64_t)temp;
        n >>= 1;
    }
    return result;
}

// Function to compute additive constant for n steps
uint64_t computeAddend(uint64_t M, uint64_t A, int n) {
    uint64_t sum = 0;
    uint64_t current = A;
    for (int i = 0; i < n; i++) {
        sum = (sum + current) & ((1ULL << 48) - 1);
        current = (__uint128_t(M) * current + A) & ((1ULL << 48) - 1);
    }
    return sum;
}

// Jump ahead function
uint64_t jumpAhead(uint64_t a0, uint64_t M_pow, uint64_t A_sum) {
    return (__uint128_t(M_pow) * a0 + A_sum) & ((1ULL << 48) - 1);
}

// Jump back function
uint64_t jumpBack(uint64_t aN, uint64_t invM_pow, uint64_t A_sum_inv) {
    return (__uint128_t(invM_pow) * (aN + ( (1ULL <<48) - A_sum_inv )) ) & ((1ULL << 48) - 1);
}

uint64_t recoverSeedPuzzleOne() {
    // 0) get b_0..b_8
    std::vector<uint8_t> puzzle = getPuzzleOneIndices();
    if (puzzle.size() != 9) {
        std::cerr << "PuzzleOne length mismatch?\n";
        std::exit(1);
    }

    // Precompute bvals for forward half and backward half
    std::vector<uint8_t> forwardBvals(puzzle.begin(), puzzle.begin()+5);
    std::vector<uint8_t> backwardBvals(puzzle.begin()+4, puzzle.end());

    // Precompute M^4 and A_sum
    const int N = 4;
    uint64_t M_pow_N = powM(MULTIPLIER, N);
    uint64_t A_sum_N = computeAddend(MULTIPLIER, ADDEND, N);
    uint64_t invM = inverseMod2to48(MULTIPLIER);
    uint64_t invM_pow_N = powM(invM, N); // Inverse multiplier to the power N
    uint64_t A_sum_inv = computeAddend(invM, ( (1ULL <<48) - ADDEND ), N); // Adjust as needed

    // Initialize lists
    std::vector<ForwardPair> forwardList;
    std::vector<BackwardPair> backwardList;
    forwardList.reserve(5'500'000'000); // Adjust based on expected matches
    backwardList.reserve(5'500'000'000);

    // Parallel Forward Pass
    #pragma omp parallel
    {
        std::vector<ForwardPair> threadForwardList;
        #pragma omp for nowait
        for (uint64_t top32 = 0; top32 < (1ULL << 32); top32++) {
            if ((top32 % 52ULL) != puzzle[0]) continue;
            for (uint64_t bottom16 = 0; bottom16 < 65536ULL; bottom16++) {
                uint64_t a0 = (top32 << 16) | bottom16;
                uint64_t a4 = jumpAhead(a0, M_pow_N, A_sum_N);
                if (getBofState(a4) == puzzle[4]) { // Check b4
                    threadForwardList.emplace_back(ForwardPair{a4, a0});
                }
            }
        }
        #pragma omp critical
        forwardList.insert(forwardList.end(), threadForwardList.begin(), threadForwardList.end());
    }

    // Parallel Backward Pass
    #pragma omp parallel
    {
        std::vector<BackwardPair> threadBackwardList;
        #pragma omp for nowait
        for (uint64_t top32 = 0; top32 < (1ULL << 32); top32++) {
            if ((top32 % 52ULL) != puzzle[8]) continue;
            for (uint64_t bottom16 = 0; bottom16 < 65536ULL; bottom16++) {
                uint64_t a8 = (top32 << 16) | bottom16;
                uint64_t a4 = jumpBack(a8, invM_pow_N, A_sum_inv);
                if (getBofState(a4) == puzzle[4]) { // Check b4
                    threadBackwardList.emplace_back(BackwardPair{a4, a8});
                }
            }
        }
        #pragma omp critical
        backwardList.insert(backwardList.end(), threadBackwardList.begin(), threadBackwardList.end());
    }

    // Sort both lists
    auto compareForward = [](const ForwardPair& a, const ForwardPair& b) -> bool {
        return a.a4 < b.a4;
    };
    auto compareBackward = [](const BackwardPair& a, const BackwardPair& b) -> bool {
        return a.a4 < b.a4;
    };

    std::sort(forwardList.begin(), forwardList.end(), compareForward);
    std::sort(backwardList.begin(), backwardList.end(), compareBackward);

    // Perform Intersection
    size_t f = 0, bck = 0;
    uint64_t finalSeed = 0;
    bool foundSeed = false;

    while (f < forwardList.size() && bck < backwardList.size()) {
        if (forwardList[f].a4 < backwardList[bck].a4) {
            f++;
        }
        else if (forwardList[f].a4 > backwardList[bck].a4) {
            bck++;
        }
        else {
            // Collect all ForwardPairs with this a4
            uint64_t current_a4 = forwardList[f].a4;
            size_t f_start = f;
            while (f < forwardList.size() && forwardList[f].a4 == current_a4) f++;
            // Collect all BackwardPairs with this a4
            size_t b_start = bck;
            while (bck < backwardList.size() && backwardList[bck].a4 == current_a4) bck++;
            // Cross product
            for (size_t i = f_start; i < f; i++) {
                for (size_t j = b_start; j < bck; j++) {
                    uint64_t a0 = forwardList[i].a0;
                    if (matchesPuzzleOne(a0, puzzle)) {
                        finalSeed = a0;
                        foundSeed = true;
                        break;
                    }
                }
                if (foundSeed) break;
            }
            if (foundSeed) break;
        }
    }

    if (!foundSeed) {
        std::cerr << "ERROR: No seed found that starts with \"PuzzleOne\"?!\n";
        std::exit(1);
    }

    return finalSeed;
}
