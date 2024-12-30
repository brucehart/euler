#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>

// Hard-coded limit: N = 10^17
static const uint64_t kMaxN = 100000000000000000ULL; 

// We'll store all cubes < N in arrCubes.
// We'll keep partial sums in mapKnownS: mapKnownS[x] = F(x) = sum_{n=0..x} D(n).
std::vector<uint64_t> arrCubes;         
std::map<uint64_t, uint64_t> mapKnownS; 

// ----------------------------------------------------------------------------
// computeSum(x) ~ solve_for_S_n(n): returns F(x)
// where F(x) = sum_{n=0..x} D(n), D(n) = # steps to reduce n to 0
// by subtracting largest cube <= n.
// ----------------------------------------------------------------------------
uint64_t computeSum(uint64_t x) {
    // If we already have it, return quickly
    auto itFind = mapKnownS.find(x);
    if (itFind != mapKnownS.end()) {
        return itFind->second;
    }

    // Otherwise we find the largest cube below x:
    //   We want the insertion position for x in arrCubes so that
    //   arrCubes[pos] >= x. So we do lower_bound.
    //   Then largest_cube_below = arrCubes[pos-1].
    // BUT watch edge cases if x < arrCubes[1].
    auto itLB = std::lower_bound(arrCubes.begin(), arrCubes.end(), x);
    // If x is strictly greater than every element in arrCubes, itLB=arrCubes.end().
    // If x is in the array exactly, itLB points to x. We want strictly below x => 
    // we subtract 1 from the iterator.
    // If x < arrCubes[1], we want to get arrCubes[0]=0.
    if (itLB == arrCubes.begin()) {
        // Means x <= 0 in normal usage => x=0 handled earlier, so likely won't happen
        // But let's be safe:
        uint64_t largestCubeBelow = 0ULL;
        uint64_t gap = x - largestCubeBelow; 
        // val = F(0) + gap + F(gap)
        uint64_t valRes = mapKnownS[0ULL] + gap + computeSum(gap);
        mapKnownS[x] = valRes;
        return valRes;
    }

    // We do "itLB - 1" to get the largest element < x if x not itself in arrCubes,
    // or if x is exactly a cube, "itLB" points to x. 
    // That is the largest index where arrCubes[idx] < x (strictly).
    auto itLargestBelow = itLB;
    if (itLargestBelow != arrCubes.begin()) {
        --itLargestBelow;
    }
    uint64_t largestCubeBelow = *itLargestBelow;
    if (largestCubeBelow >= x && itLargestBelow != arrCubes.begin()) {
        // If x is actually a cube, largestCubeBelow==x (not below).
        // So let's decrement once more if they are equal.
        if (largestCubeBelow == x && itLargestBelow != arrCubes.begin()) {
            --itLargestBelow;
            largestCubeBelow = *itLargestBelow;
        }
    }

    // gap = n - largest_cube_below
    uint64_t gap = x - largestCubeBelow;

    // val = known_S[largest_cube_below] + gap + solve_for_S_n(gap)
    // We'll look up known_S for largestCubeBelow:
    uint64_t baseVal = 0ULL;
    auto itBase = mapKnownS.find(largestCubeBelow);
    if (itBase != mapKnownS.end()) {
        baseVal = itBase->second;
    } else {
        // theoretically it should exist if largestCubeBelow is in arrCubes
        // or if it's small. But let's just compute it safely:
        baseVal = computeSum(largestCubeBelow);
    }

    uint64_t valOutcome = baseVal + gap + computeSum(gap);

    // store in mapKnownS
    mapKnownS[x] = valOutcome;
    return valOutcome;
}

int main() {
    // 1) Build the array of cubes below kMaxN
    arrCubes.reserve(500000); // just a guess, large enough for ~464k cubes
    arrCubes.push_back(0ULL);

    uint64_t iVal = 1ULL;
    while (true) {
        // iVal^3 can overflow if iVal too large, but for ~464,159^3 it's still < 2^64.
        // We'll break if iVal^3 >= kMaxN.
        // Check carefully to avoid overflow: (iVal <= 464159) is safe enough.
        uint64_t c3 = (uint64_t)iVal * iVal * iVal;
        if (c3 >= kMaxN) {
            break;
        }
        arrCubes.push_back(c3);
        iVal++;
    }

    // 2) Initialize mapKnownS with small values:
    //    for n in [0..7], define F(n) explicitly.
    //    but we also do F(0)=0.
    mapKnownS[0ULL] = 0ULL;
    for (uint64_t smallVal = 1ULL; smallVal < 8ULL; ++smallVal) {
        mapKnownS[smallVal] = smallVal + mapKnownS[smallVal - 1ULL];
    }

    // 3) Build partial sums for each cube. 
    //    For each arrCubes[i] (where i >= 2 because 0,1 are trivial),
    //    we ensure mapKnownS[curCube - 1] is computed, then store mapKnownS[curCube].
    for (std::size_t idxCube = 2; idxCube < arrCubes.size(); ++idxCube) {
        uint64_t currentCube = arrCubes[idxCube];
        // Make sure F(currentCube - 1) is in mapKnownS
        // Then define F(currentCube) = F(currentCube - 1) + 1
        if (currentCube > 0ULL) {
            uint64_t valBelow = computeSum(currentCube - 1ULL);
            mapKnownS[currentCube] = valBelow + 1ULL; 
        } else {
            // currentCube == 0 won't happen here because idxCube>=2
        }
    }

    // 4) Finally compute F(kMaxN - 1) and print.    
    uint64_t ans = computeSum(kMaxN - 1ULL);
    std::cout << ans << std::endl;

    return 0;
}

