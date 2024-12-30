#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstdint>   // for std::int64_t, etc.

static const int N = 51;

//------------------------------------------------------------------------------
// A function to build all subset sums (meet-in-the-middle for half the array).
//   - w[i]    = the numeric value (+/-) for the i-th student's log-likelihood contribution
//   - pPlus[i]= probability that the i-th student's contribution is +w[i]
//   - pMinus[i]= probability that the i-th student's contribution is -w[i]
// We generate all 2^nHalf possible subsets from 'start' to 'start + nHalf - 1',
// storing (subsetSum, logProbOfThatSubset).
//
// Because the direct probability might underflow, we store logProb in double.
//
// Return a vector of (sumValue, logProb), unsorted.
//
void buildSubsets(const std::vector<double>& w,
                  const std::vector<double>& pPlus,
                  const std::vector<double>& pMinus,
                  int start,
                  int nHalf,
                  std::vector<std::pair<double,double>>& out)
{
    out.reserve((std::size_t)1 << nHalf); // 2^nHalf
    out.clear();

    // We will do a simple recursive or iterative generation.  
    // Here is a recursive version for clarity.
    // For serious performance, an iterative bit-trick approach is often faster.
    std::function<void(int, double, double)> dfs = [&](int idx, double sumVal, double logP) {
        if (idx == start + nHalf) {
            out.emplace_back(sumVal, logP);
            return;
        }
        // Option 1: choose +w[idx]
        {
            double newSum  = sumVal + w[idx];
            double newLogP = logP + std::log(pPlus[idx]);
            dfs(idx+1, newSum, newLogP);
        }
        // Option 2: choose -w[idx]
        {
            double newSum  = sumVal - w[idx];
            double newLogP = logP + std::log(pMinus[idx]);
            dfs(idx+1, newSum, newLogP);
        }
    };

    dfs(start, 0.0, 0.0);
}

//------------------------------------------------------------------------------
// Given a sorted vector of (sumValue, logProb), build a "suffix sum" array so that
// suffixSum[i] = sum_{j >= i} of exp( logProb[j] ) in normal double precision.
// This allows quick queries of "sum of probabilities for all sums >= some cutoff".
//
std::vector<double> buildSuffixProbArray(const std::vector<std::pair<double,double>>& vec)
{
    // We'll do suffix from right to left.  All sum of exp(logProb) <= 1.0 for each half,
    // but watch for floating accumulations.
    int sz = (int)vec.size();
    std::vector<double> suffix(sz+1, 0.0);  // suffix[sz] = 0, suffix[sz-1], ...
    // We'll accumulate in normal space, using a partial technique to reduce rounding.
    double running = 0.0;
    for (int i = sz-1; i >= 0; --i) {
        // add exp(logProb[i])
        running += std::exp(vec[i].second);
        suffix[i] = running;
    }
    return suffix;
}

//------------------------------------------------------------------------------
// Compute Probability( sum >= 0 ) using meet-in-the-middle approach:
//   1) build all subset sums for first half => A
//   2) build all subset sums for second half => B
//   3) sort B by sumValue
//   4) build suffix array for probabilities in B
//   5) for each entry in A, do a binary search in B for sums >= -A[i].sumValue
//   6) multiply the probabilities and accumulate
//
double computeProbSumGeqZero(const std::vector<double>& w,
                             const std::vector<double>& pPlus,
                             const std::vector<double>& pMinus)
{
    int n = (int)w.size();
    int half1 = n/2;          // e.g. 25 if n=51
    int half2 = n - half1;    // e.g. 26

    // 1) build for first half
    std::vector<std::pair<double,double>> A;
    buildSubsets(w, pPlus, pMinus, 0, half1, A);

    // 2) build for second half
    std::vector<std::pair<double,double>> B;
    buildSubsets(w, pPlus, pMinus, half1, half2, B);

    // 3) sort B by sumValue ascending
    std::sort(B.begin(), B.end(),
              [](auto &a, auto &b){
                  return a.first < b.first;  // sort by sumValue
              });

    // 4) suffix array for probabilities in B
    std::vector<double> suffixB = buildSuffixProbArray(B);

    // Probability that sum >= 0
    double probSumGeq0 = 0.0;

    // For convenience:
    // B[i].first  = sumValue in second half
    // B[i].second = logProb in second half
    // suffixB[i]  = sum of exp(logProb) from i..end

    // 5) for each entry in A, find index in B
    //    so that B[j].first >= -A[i].first
    //    i.e. j = lower_bound of (-A[i].first)
    //    Then the sum of probabilities for those j..end is suffixB[j].
    //
    //    We then multiply that by exp(A[i].second).
    //
    for (auto &aPair : A) {
        double sumA   = aPair.first;
        double logPrA = aPair.second;

        double target = -sumA; // we want B[j].first >= target

        // binary search in B
        // "std::lower_bound" to find the first index where B[i].first >= target
        auto it = std::lower_bound(
            B.begin(), B.end(),
            target,
            [](const std::pair<double,double>& x, double val){
                return x.first < val;
            }
        );
        int idx = (int)std::distance(B.begin(), it);
        if (idx < (int)B.size()) {
            double partialSum = suffixB[idx];
            // multiply partialSum by exp(logPrA) in normal space
            double thisContribution = std::exp(logPrA) * partialSum;
            probSumGeq0 += thisContribution;
        }
    }

    return probSumGeq0;
}

//------------------------------------------------------------------------------
// Main solves the specific problem for p_i in {0.25, 0.26, ..., 0.75}.
// We want Probability of correct guess to 10 decimal places.
//
// Probability(correct) = 0.5 * Pr_H[ S >= 0 ] + 0.5 * Pr_T[ S < 0 ]
//                      = 0.5 + 0.5 * ( Pr_H[ S >= 0 ] - Pr_T[ S >= 0 ] ).
//
int main()
{
    // 1) Construct the 51 probabilities p_i = 0.25, 0.26, ..., 0.75
    std::vector<double> p(51);
    for (int i = 0; i < 51; i++) {
        p[i] = 0.25 + 0.01 * i;  // 0.25, 0.26, ..., 0.75
    }

    // 2) Build w[i] = ln((1 - p[i]) / p[i]) for i=0..50
    std::vector<double> w(51);
    for (int i = 0; i < 51; i++) {
        w[i] = std::log((1.0 - p[i]) / p[i]);
    }

    // 3) Build "plus probability" / "minus probability" for the Heads scenario:
    //    - plusProb[i] = 1 - p[i]
    //    - minusProb[i] = p[i]
    //    Then Pr_H[S >= 0] = computeProbSumGeqZero(...)
    {
        std::vector<double> pPlus_H(51), pMinus_H(51);
        for (int i = 0; i < 51; i++) {
            pPlus_H[i]  = 1.0 - p[i];
            pMinus_H[i] = p[i];
        }
        double probHeadsGe0 = computeProbSumGeqZero(w, pPlus_H, pMinus_H);

        // 4) Build for the Tails scenario:
        //    - plusProb[i] = p[i]
        //    - minusProb[i] = 1 - p[i]
        std::vector<double> pPlus_T(51), pMinus_T(51);
        for (int i = 0; i < 51; i++) {
            pPlus_T[i]  = p[i];
            pMinus_T[i] = 1.0 - p[i];
        }
        double probTailsGe0 = computeProbSumGeqZero(w, pPlus_T, pMinus_T);

        // 5) Probability of correct
        double probCorrect =
            0.5 + 0.5 * (probHeadsGe0 - probTailsGe0);

        // 6) Output with 10 digits after decimal point
        std::cout << std::fixed << std::setprecision(10)
                  << probCorrect << std::endl;
    }

    return 0;
}

