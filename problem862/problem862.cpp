#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // For std::accumulate
#include <functional>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

typedef cpp_int BigInt;

// Precompute factorials up to MAX_K!
const int MAX_K = 12;
vector<BigInt> fact(MAX_K + 1);

void compute_factorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAX_K; ++i) {
        fact[i] = fact[i - 1] * i;
    }
}

// Function to compute multinomial coefficient
BigInt multinomial(int n, const vector<int>& counts) {
    BigInt res = fact[n];
    for (int count : counts) {
        res /= fact[count];
    }
    return res;
}

// Function to generate all combinations of counts c0..c9 where sum(ci) = k and c0 <= k - 1
void generate_combinations(int k, vector<vector<int>>& combinations) {
    vector<int> counts(10, 0);  // counts[0] to counts[9] for digits 0 to 9
    function<void(int, int)> dfs = [&](int pos, int remaining) {
        if (pos == 10) {
            if (remaining == 0 && counts[0] <= k - 1) {
                combinations.push_back(counts);
            }
            return;
        }
        for (int i = 0; i <= remaining; ++i) {
            counts[pos] = i;
            dfs(pos + 1, remaining - i);
        }
    };
    dfs(0, k);
}

int main() {
    compute_factorials();

    BigInt total_S = 0;

    const int k = 12;  // Number of digits

    vector<vector<int>> combinations;
    generate_combinations(k, combinations);

    for (const auto& counts : combinations) {
        // counts[0] to counts[9] correspond to digits 0 to 9
        int c0 = counts[0];  // Number of zeros
        if (c0 > k - 1) continue;  // Leading digit cannot be zero

        // Compute N_total: Total permutations including those starting with zero
        BigInt N_total = multinomial(k, counts);

        // Compute N_zero_leading: Permutations where the first digit is zero
        BigInt N_zero_leading = (N_total * c0) / k;

        // Compute N_valid: Valid permutations (numbers without leading zeros)
        BigInt N_valid = N_total - N_zero_leading;

        if (N_valid < 2) continue;  // Need at least two numbers to have a larger permutation

        // Compute total T for this combination
        BigInt sum_T = N_valid * (N_valid - 1) / 2;

        // Accumulate total_S
        total_S += sum_T;
    }

    cout << total_S << endl;

    return 0;
}
