#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

/*
  This program determines how many pairs of non-empty, disjoint subsets
  of a strictly increasing set of size n=12 must be "tested" for the
  possibility that their sums could be equal.

  Key points/constraints from the problem:
  1) The set has n distinct, strictly increasing elements (e.g., 1 < 2 < ... < n).
  2) If B and C are subsets with different cardinalities, then S(B) != S(C).
     (Already guaranteed by the problem statement, so we only need to
     compare subsets of the same size.)
  3) We only compare non-empty, disjoint subsets (B ï C = í, B != í, C != í).
  4) A pair (B, C) is counted if there is any chance S(B) = S(C) could be true.
     In other words, if the structure of B and C does *not* force S(B) < S(C)
     or S(B) > S(C) outright by virtue of the set's strictly increasing nature,
     we must test the pair.

  High-level approach:
  --------------------
  1) Generate all subsets of {1, 2, ..., n} as bitmasks from 1..(1<<n)-1.
  2) Group subsets by their cardinality (popcount).
  3) For each cardinality k, consider pairs of subsets of size k:
        - If they are disjoint (bitwise AND == 0),
          check if their elements are "strictly aligned" or "strictly misaligned."
        - If one subset's elements are all strictly smaller than the other's
          in sorted order, then S(B) < S(C) must hold (no chance of equality).
        - If one subset's elements are all strictly larger than the other's,
          then S(B) > S(C) must hold.
        - Otherwise, there is some interleaving of elements, and
          S(B) = S(C) is *possible*; we count that pair as "needing testing."

  Complexity considerations:
  --------------------------
  - There are 2^n subsets in total (4096 when n=12).
  - We group them by size k, where 0 <= k <= n.
  - The largest binomial coefficient for n=12 is C(12, 6) = 924, still small
    enough to allow pairwise checks in a straightforward manner.
  - Disjointness check is done via a quick bitwise AND.
  - The sorted-order check is done in O(k), which is at most 12.

  This direct method is efficient enough for n=12 and follows the problem's
  requirement of not relying on approximation, but rather an exact check.
*/

// Return a list of set-bit positions in ascending order.
// E.g., if x = 0b10110, then this returns {1, 2, 4}.
static std::vector<int> getSetBits(unsigned int x)
{
    std::vector<int> bits;
    while (x != 0) {
        int lowest = __builtin_ctz(x);  // Count trailing zeros (GCC/Clang builtin)
        bits.push_back(lowest);
        x ^= (1U << lowest);
    }
    return bits;
}

// Returns true if subsets represented by bMask and cMask might possibly
// have the same sum. This happens if and only if neither set of elements
// is strictly smaller nor strictly larger than the other in sorted order.
static bool needTesting(unsigned int bMask, unsigned int cMask)
{
    // Get sorted list of set-bit indices for each subset
    std::vector<int> bBits = getSetBits(bMask);
    std::vector<int> cBits = getSetBits(cMask);

    // Both subsets have the same cardinality (assured by calling context).
    // Let that cardinality be k.
    // Check if bBits[i] < cBits[i] for all i
    // or bBits[i] > cBits[i] for all i
    // If either is true, sums can't be equal. Otherwise, we must test them.
    bool allBltC = true;  // True if for all i, bBits[i] < cBits[i]
    bool allBgtC = true;  // True if for all i, bBits[i] > cBits[i]

    for (size_t i = 0; i < bBits.size(); i++) {
        if (bBits[i] >= cBits[i]) {
            allBltC = false;
        }
        if (bBits[i] <= cBits[i]) {
            allBgtC = false;
        }
        // If neither "all smaller" nor "all larger" can hold, we can stop
        if (!allBltC && !allBgtC) {
            return true;  // Must test
        }
    }
    // If we exit the loop with allBltC or allBgtC still true, no test needed
    return false;
}

int main()
{
    // For this specific problem, n = 12
    const int n = 12;

    // Precompute all subsets by cardinality
    // We'll skip the empty subset (cardinality=0) because the problem
    // wants non-empty subsets only.
    std::vector<unsigned int> subsetsBySize[13];  // index = 0..12
    subsetsBySize[0].clear(); // Not used, but let's keep it for completeness

    // Generate all non-empty subsets
    // Use bitmask from 1 to (1<<n)-1
    for (unsigned int mask = 1; mask < (1U << n); mask++) {
        // Count bits using a builtin function for speed.
        // Alternatively, one can do a manual bit-count loop.
        int popCount = __builtin_popcount(mask);
        subsetsBySize[popCount].push_back(mask);
    }

    // Now, we want to count how many pairs need testing.
    // We only compare subsets of the *same* cardinality k.
    // Also skip k=0 (empty) and k>n (impossible).
    // Because of the second property (different cardinalities => no equal sums),
    // we never compare subsets of different sizes.
    long long result = 0;

    // For each cardinality k, consider all pairs of subsets of that size.
    // We'll do i < j to avoid double-counting and to treat pairs as unordered.
    for (int k = 1; k <= n - 1; k++) {
        const auto &group = subsetsBySize[k];
        for (size_t i = 0; i < group.size(); i++) {
            for (size_t j = i + 1; j < group.size(); j++) {
                unsigned int bMask = group[i];
                unsigned int cMask = group[j];
                // Check disjointness quickly
                if ((bMask & cMask) == 0) {
                    // If they might have same sum, we increment our counter
                    if (needTesting(bMask, cMask)) {
                        result++;
                    }
                }
            }
        }
    }

    std::cout << result << std::endl;
    return 0;
}

