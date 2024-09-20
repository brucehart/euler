#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // For std::accumulate
#include <functional>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

const uint64_t MOD = 1123455689;

typedef cpp_int BigInt;

// Function to compute multinomial coefficient without divisions
BigInt multinomial(const vector<int>& counts) {
    BigInt res = 1;
    int n = accumulate(counts.begin(), counts.end(), 0);

    // Multiply numerator factors
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }

    // Divide by denominator factors
    for (int count : counts) {
        for (int i = 1; i <= count; ++i) {
            res /= i;
        }
    }

    return res;
}

// Function to generate all combinations of counts x1..x9 where sum(xi) = k
void generate_combinations(int k, vector<vector<int>> &combinations) {
    vector<int> counts(9, 0);
    function<void(int, int)> dfs = [&](int pos, int remaining) {
        if (pos == 9) {
            if (remaining == 0) {
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
    const int MAX_L = 18;

    BigInt total_S = 0;

    // Iterate over total length from 1 to MAX_L
    for (int L = 1; L <= MAX_L; ++L) {
        //std::cout << "L = " << L << std::endl;
        // Iterate over number of non-zero digits from 1 to L
        for (int k = 1; k <= L; ++k) {
            vector<vector<int>> combinations;
            generate_combinations(k, combinations);

            // For each combination of counts x1..x9 where sum(xi) = k
            for (const auto& counts : combinations) {
                // counts for digits 1 to 9
                int x0 = L - k;  // Number of zeros

                if (x0 < 0) continue;

                vector<int> total_counts = counts;
                total_counts.insert(total_counts.begin(), x0);  // Insert count for zero at the beginning

                // Compute N1: total permutations with counts including zeros
                BigInt N1 = multinomial(total_counts);

                // Compute N2: permutations where the first digit is zero (invalid numbers)
                BigInt N2 = 0;
                if (x0 >= 1) {
                    vector<int> counts_zero_first = counts;
                    counts_zero_first.insert(counts_zero_first.begin(), x0 - 1);
                    BigInt N2_temp = multinomial(counts_zero_first);
                    N2 = N2_temp;
                }

                BigInt N = N1 - N2;

                if (N == 0) continue;

                // Compute f(d)
                BigInt f_d = 0;
                for (int digit = 1; digit <= 9; ++digit) {
                    for (int cnt = 0; cnt < counts[digit - 1]; ++cnt) {
                        f_d = f_d * 10 + digit;
                    }
                }

                // Perform modulo operations carefully
                BigInt N_mod = N % MOD;
                BigInt f_d_mod = f_d % MOD;
                total_S = (total_S + (N_mod * f_d_mod) % MOD) % MOD;
            }
        }
    }

    cout << total_S << endl;

    return 0;
}
