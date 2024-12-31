#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <cassert>

// ------------------------------------------------------------
// LCG definitions
// ------------------------------------------------------------
static const uint64_t MODULUS    = (1ULL << 48);
static const uint64_t MULTIPLIER = 25214903917ULL;
static const uint64_t ADDEND     = 11ULL;

// Return the next LCG state
uint64_t nextRand48(uint64_t state) {
    // (MULTIPLIER * state + ADDEND) mod 2^48
    // In C++, 64-bit unsigned multiplication overflows naturally mod 2^64;
    // we then mask to 48 bits.
    __uint128_t temp = ( (__uint128_t)MULTIPLIER * state ) + ADDEND;
    uint64_t result  = (uint64_t)temp & ((1ULL << 48) - 1);
    return result;
}

// Return the previous LCG state (by using the modular inverse of MULTIPLIER)
uint64_t prevRand48(uint64_t state, uint64_t invM) {
    // a_{n} = M^{-1} * (a_{n+1} - A) mod 2^48
    // We have to do the subtraction mod 2^48.
    uint64_t tmp = (state + (MODULUS - ADDEND)) & (MODULUS - 1);
    // multiply by inverse
    __uint128_t temp = ( (__uint128_t)invM * tmp );
    uint64_t result  = (uint64_t)temp & ((1ULL << 48) - 1);
    return result;
}

// ------------------------------------------------------------
// Map LCG state -> character:  c_n = mapToChar(a_n)
// b_n = (a_n >> 16) mod 52
// ------------------------------------------------------------
char mapToChar(uint64_t state) {
    uint64_t topBits = state >> 16; 
    uint64_t idx52   = topBits % 52;
    if (idx52 < 26) {
        return static_cast<char>('a' + idx52);
    } else {
        return static_cast<char>('A' + (idx52 - 26));
    }
}

// Convert a char in [a-zA-Z] back to 0..51
// Return 255 if invalid.
uint8_t charToIndex(char c) {
    if (c >= 'a' && c <= 'z') {
        return static_cast<uint8_t>(c - 'a'); // 0..25
    }
    if (c >= 'A' && c <= 'Z') {
        return static_cast<uint8_t>(26 + (c - 'A')); // 26..51
    }
    return 255; // invalid
}

// ------------------------------------------------------------
// Compute M^{-1} mod 2^48 using Extended Euclid or
// an adaptation of the binary GCD. In 2^k with M odd, 
// the inverse always exists. 
// ------------------------------------------------------------

// A simple function for xgcd in normal arithmetic won't work directly
// mod 2^48 because 2^48 is not prime. However, since MULTIPLIER is odd,
// it *is* invertible mod 2^48. We can compute that inverse with
// an algorithm specialized for 2^n and an odd number.
uint64_t inverseMod2to48(uint64_t odd) {
    // We want odd * inv = 1 mod 2^48.
    // One known method: we can use the fact that for an odd integer a,
    //    a * (2 - a) = 1 mod 2^2
    // then repeatedly apply a "Newton iteration" doubling trick to get up to 2^48.
    // Pseudocode reference: "Hacker's Delight" or similar sources.

    // We'll do 8 expansions from 2^1 to 2^2 -> 2^4 -> 2^8 -> ... -> 2^48
    // Start with inv mod 2^1. trivially odd * 1 = 1 mod 2 => inv=1.
    uint64_t inv = 1;
    for (int i = 0; i < 6; i++) {
        // inv = inv * (2 - a*inv) mod 2^(2^(i+1)) each iteration
        // but we are going up in powers of two more quickly. We'll just do:
        //   inv = inv * (2 - odd*inv)  (mask to appropriate bits)
        uint64_t product = (odd * inv);
        uint64_t delta   = (2ULL - (product & ((1ULL << (1 << i)) - 1)));
        inv = (inv * delta);
    }
    // Now inv is correct mod 2^64, we only need 2^48. We'll just mask:
    inv &= ((1ULL << 48) - 1);
    // A quick "Newton" style iteration for 2^48 specifically:
    //   inv = inv * (2 - odd*inv mod 2^48) mod 2^48
    {
        __uint128_t tmp   = ( (__uint128_t)odd * inv ) & ( (1ULL << 48) - 1 );
        uint64_t     diff = (2ULL - (uint64_t)tmp);
        __uint128_t fix   = ( (__uint128_t)inv * diff );
        inv = (uint64_t)fix & ((1ULL << 48) - 1);
    }
    return inv;
}

// ------------------------------------------------------------
// Generate b_0..b_8 from "PuzzleOne"
// ------------------------------------------------------------
std::vector<uint8_t> getPuzzleOneIndices() {
    // "PuzzleOne" is 9 chars
    const std::string prefix = "PuzzleOne";
    std::vector<uint8_t> result;
    result.reserve(prefix.size());
    for (char c : prefix) {
        uint8_t idx = charToIndex(c);
        if (idx == 255) {
            std::cerr << "Invalid puzzle prefix character: " << c << "\n";
            std::exit(1);
        }
        result.push_back(idx);
    }
    return result;
}

// ------------------------------------------------------------
// Check if a given 48-bit state yields the 9-char prefix "PuzzleOne"
// We do this by stepping forward from a0, comparing each b_n
// to puzzleOneIndices[n]. 
// ------------------------------------------------------------
bool matchesPuzzleOne(uint64_t a0, const std::vector<uint8_t>& puzzleOneIndices) {
    uint64_t state = a0;
    for (size_t i = 0; i < puzzleOneIndices.size(); i++) {
        uint64_t topBits = state >> 16;
        uint64_t b       = topBits % 52;
        if (b != puzzleOneIndices[i]) {
            return false;
        }
        // next
        state = nextRand48(state);
    }
    return true;
}

// ------------------------------------------------------------
// Step A: Recover the 48-bit seed that yields "PuzzleOne" as
//         the first 9 characters.
// 
// We'll do a meet-in-the-middle on indices 0->4 and 8->4.
// (That is 4 transitions forward, 4 transitions backward.)
//
// High-level outline:
//
//  1) Precompute puzzleOneIndices b_0..b_8.
//  2) Forward pass: 
//       - For each possible top32 a_0>>16 that yields b_0, 
//         expand 4 steps (0->1->2->3->4).  Keep only states
//         that match b_1..b_4.  Store (a_4 -> a_0) in a map.
//  3) Backward pass: 
//       - For each possible top32 a_8>>16 that yields b_8, 
//         step backward 4 times (8->7->6->5->4). Keep only
//         states that match b_7..b_4.  Store (a_4 -> a_8).
//  4) Intersect on a_4. For each intersection, we have a
//     candidate a_0. Validate the entire 9 steps. 
//  5) Return the unique a_0 found.
//
// Even this can be large. Typically you'd add heavy pruning
// or multi-stage meet. Shown here in simplest conceptual form.
// ------------------------------------------------------------

// Helper to compute b_i of a state quickly
static inline uint64_t getBofState(uint64_t st) {
    return (st >> 16) % 52ULL;
}

// We'll store the forward results in a map from a4 -> a0
// If collisions happen, we might store multiple a0 in a vector.
using ForwardMap = std::unordered_map<uint64_t, std::vector<uint64_t>>;

// We'll store the backward results in a map from a4 -> a8
using BackwardMap = std::unordered_map<uint64_t, std::vector<uint64_t>>;


// Step forward 4 times from an initial state (checking each b_i)
uint64_t forward4(uint64_t start, const std::vector<uint8_t>& bvals, bool& ok) {
    // bvals has length 5: b_0..b_4
    // start is a_0
    // We check if a_0 matches b_0 etc.
    uint64_t st = start;
    for (int i = 0; i < 5; i++) {
        if (getBofState(st) != bvals[static_cast<size_t>(i)]) {
            ok = false;
            return 0;
        }
        if (i < 4) {
            st = nextRand48(st);
        }
    }
    // st is now a_4
    ok = true;
    return st;
}

// Step backward 4 times from final state (checking each b_i in reverse)
uint64_t backward4(uint64_t end, const std::vector<uint8_t>& bvals, bool& ok, uint64_t invM) {
    // bvals has length 5: b_4..b_8
    // end is a_8
    // We want to see if a_8 matches b_8, then a_7 matches b_7, etc
    // We'll step backward in a loop.
    uint64_t st = end;
    for (int i = 4; i >= 0; i--) {
        if (getBofState(st) != bvals[static_cast<size_t>(i)]) {
            ok = false;
            return 0;
        }
        if (i > 0) {
            st = prevRand48(st, invM);
        }
    }
    // st is now a_4
    ok = true;
    return st;
}


uint64_t recoverSeedPuzzleOne() {
    // 0) get b_0..b_8
    std::vector<uint8_t> puzzle = getPuzzleOneIndices();
    if (puzzle.size() != 9) {
        std::cerr << "PuzzleOne length mismatch?\n";
        std::exit(1);
    }

    // Precompute bvals for forward half and backward half
    // forward half: b_0..b_4
    std::vector<uint8_t> forwardBvals(puzzle.begin(), puzzle.begin()+5);
    // backward half: b_4..b_8
    std::vector<uint8_t> backwardBvals(puzzle.begin()+4, puzzle.end());

    // We'll compute the modular inverse of MULTIPLIER mod 2^48
    uint64_t invM = inverseMod2to48(MULTIPLIER);

    // 1) Forward pass map (a4 -> list of a0)
    ForwardMap forwardMap;
    forwardMap.reserve(1'000'000); // guess a big enough reserve to reduce rehashes

    // We iterate over all possible top32 values for a_0 (that match b_0).
    // top32 = a_0 >> 16 in [0..2^32).
    // We want top32 % 52 == b_0.  Then we combine with bottom16 in [0..65535].
    uint64_t b0 = puzzle[0];
    for (uint64_t top32 = 0; top32 < (1ULL << 32); top32++) {
        if ((top32 % 52ULL) != b0) {
            continue;
        }
        // For each bottom16:
        //   a_0 = (top32 << 16) | bottom16
        // Then do forward4 steps; if we match b_0..b_4, store a_4 -> a_0
        for (uint64_t bottom16 = 0; bottom16 < 65536ULL; bottom16++) {
            uint64_t a0 = (top32 << 16) | bottom16;
            bool ok = false;
            uint64_t a4 = forward4(a0, forwardBvals, ok);
            if (ok) {
                forwardMap[a4].push_back(a0);
            }
        }
    }

    // 2) Backward pass map (a4 -> list of a8)
    BackwardMap backwardMap;
    backwardMap.reserve(1'000'000);

    // We iterate all possible top32 for a_8 that match b_8
    uint64_t b8 = puzzle[8];
    for (uint64_t top32 = 0; top32 < (1ULL << 32); top32++) {
        if ((top32 % 52ULL) != b8) {
            continue;
        }
        for (uint64_t bottom16 = 0; bottom16 < 65536ULL; bottom16++) {
            uint64_t a8 = (top32 << 16) | bottom16;
            bool ok = false;
            uint64_t a4 = backward4(a8, backwardBvals, ok, invM);
            if (ok) {
                backwardMap[a4].push_back(a8);
            }
        }
    }

    // 3) Intersect on a_4
    // For each a_4 in forwardMap, check if it's also in backwardMap.
    // Then for each (a_0 in forwardMap[a_4]) and each (a_8 in backwardMap[a_4]),
    // we have a candidate chain. We'll do a final verification of all 9 chars
    // from a_0 to see if it matches "PuzzleOne". The puzzle states there's exactly 1 match.
    uint64_t finalSeed = 0;
    bool foundSeed = false;

    for (const auto& kv : forwardMap) {
        uint64_t a4 = kv.first;
        const auto& vecA0 = kv.second;
        auto itB = backwardMap.find(a4);
        if (itB == backwardMap.end()) {
            continue;
        }
        const auto& vecA8 = itB->second;
        // For each combination (a0, a8), check the full chain:
        for (uint64_t a0 : vecA0) {
            // We only need to check a0 once. If it truly leads to a4,
            // and from that to a8, it's consistent- but let's do the
            // simplest approach: just check the 9 chars directly from a0.
            if (matchesPuzzleOne(a0, puzzle)) {
                finalSeed = a0;
                foundSeed = true;
                break;
            }
        }
        if (foundSeed) break;
    }

    if (!foundSeed) {
        std::cerr << "ERROR: No seed found that starts with \"PuzzleOne\"?!\n";
        std::exit(1);
    }

    return finalSeed;
}

// ------------------------------------------------------------
// Step B: once the puzzle seed is known, find the first occurrence
// of "LuckyText" in the infinite stream. (Same as the earlier snippet.)
// ------------------------------------------------------------
uint64_t findFirstOccurrence(uint64_t seed, const std::string& target) {
    const size_t T = target.size();
    const size_t CHUNK_SIZE = 200000;

    std::string buffer;
    buffer.reserve(CHUNK_SIZE + T - 1);

    uint64_t globalIndex = 0;
    std::string overlap;

    while (true) {
        buffer.clear();
        buffer = overlap; // leftover from previous chunk

        // generate chunk
        for (size_t i = 0; i < CHUNK_SIZE; ++i) {
            char c = mapToChar(seed);
            seed = nextRand48(seed);
            buffer.push_back(c);
        }

        // search
        auto it = std::search(buffer.begin(), buffer.end(),
                              target.begin(), target.end());
        if (it != buffer.end()) {
            uint64_t posInBuffer = static_cast<uint64_t>(it - buffer.begin());
            return globalIndex + posInBuffer;
        }

        // prepare overlap
        if (CHUNK_SIZE >= (T - 1)) {
            overlap = buffer.substr(buffer.size() - (T - 1));
        } else {
            overlap = buffer;
        }

        globalIndex += CHUNK_SIZE;
    }

    return static_cast<uint64_t>(-1); // not found (shouldn't happen in puzzle)
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main() {
    // STEP A: recover the seed that yields "PuzzleOne" as the first 9 chars
    uint64_t puzzleSeed = recoverSeedPuzzleOne();

    // STEP B: find first occurrence of "LuckyText"
    const std::string target = "LuckyText";
    uint64_t index = findFirstOccurrence(puzzleSeed, target);

    std::cout << index << std::endl;
    return 0;
}

