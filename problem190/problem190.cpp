// Author: Bruce J. Hart <bruce.hart@gmail.com>

// Maximizing a weighted product
// Problem 190 
// Let Sm = (x1, x2, ... , xm) be the m-tuple of positive real numbers with x1 + x2 + ... + xm = m
// for which Pm = x1 * x2^2 * ... * xm^m is maximized.

// For example, it can be verified that [P10] = 4112 ([ ] is the integer part function).

// Find Σ[Pm] for 2 ≤ m ≤ 15.

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

#define M_START 2
#define M_END 15
#define DELTAS {0.01, 0.001, 0.0001, 0.00001}
#define ALPHA 100

// Function to compute P given a vector S
double computeP(const std::vector<double>& S) {
    double P = 1.0;
    for (size_t n = 0; n < S.size(); ++n) {
        P *= pow(S[n], static_cast<double>(n + 1));
    }
    return P;
}

// Function to find the maximum P for a given m
double findMaxP(int m) {
    std::vector<double> S(m, 1.0);  // Initialize S with 1.0
    std::vector<double> S_new(m);   // New vector to store changes
    std::vector<double> deltas = DELTAS;

    std::default_random_engine rand;
    std::uniform_int_distribution<int> dist(0, m - 1);
    int addIdx, subIdx;

    double maxP = computeP(S);  // Initialize maxP with initial P value
    double newP;

    int missCount = 0;

    for (double d : deltas) {
        while (missCount < ALPHA) {
            std::copy(S.begin(), S.end(), S_new.begin());
            addIdx = dist(rand);
            subIdx = dist(rand);

            // Ensure the element to be decreased is greater than the delta
            if (S_new[subIdx] > d) {
                S_new[addIdx] += d;
                S_new[subIdx] -= d;
            }

            newP = computeP(S_new);

            // If new P is greater, update maxP and reset missCount
            if (newP > maxP) {
                maxP = newP;
                std::copy(S_new.begin(), S_new.end(), S.begin());
                missCount = 0;
            } else {
                ++missCount;
            }
        }
        missCount = 0;  // Reset missCount for the next delta
    }

    return maxP;
}

int main() {
    double maxP;
    int maxPSum = 0;

    // Iterate over the range from M_START to M_END
    for (int m = M_START; m <= M_END; ++m) {
        maxP = findMaxP(m);
        maxPSum += static_cast<int>(std::floor(maxP));  // Add the integer part of maxP to the sum
    }

    std::cout << maxPSum << std::endl;  // Output the final result
    return 0;
}
