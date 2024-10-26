#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

const int n_digits = 10;
const int MAX_MASK = 1 << n_digits;
const int len_n = 18; // Since n = 10^18
const int MOD = 1000267129;

// Precompute powers[k][L], where powers[k][L] = k^L % MOD
int64_t powers[11][19]; // k from 0 to 10, L from 0 to 18

void precompute_powers() {
    for (int k = 0; k <= n_digits; ++k) {
        powers[k][0] = 1; // k^0 = 1
        for (int L = 1; L <= len_n; ++L) {
            powers[k][L] = (powers[k][L - 1] * k) % MOD;
        }
    }
}

// Function to compute count_numbers(D_S, L)
// D_S: digits in the set D_S
// L: length of numbers
// Returns N(S) modulo MOD
int64_t count_numbers(const std::vector<int>& D_S, int L) {
    int k_S = D_S.size();
    if (k_S == 0) return 0;

    bool has_zero = std::find(D_S.begin(), D_S.end(), 0) != D_S.end();

    int64_t N_S = 0;
    if (has_zero) {
        if (k_S == 1 && has_zero) {
            N_S = 0; // Only zero in D_S, cannot form valid numbers
        } else {
            int64_t k_S_minus_1 = k_S - 1;
            int64_t pow_result = powers[k_S][L - 1];
            N_S = (k_S_minus_1 * pow_result) % MOD;
        }
    } else {
        N_S = powers[k_S][L];
    }
    return N_S;
}

int main() {
    precompute_powers();

    std::vector<int64_t> freq(MAX_MASK, 0);
    cpp_int total_numbers_total = 0;

    // For each digit mask m
    for (int m = 1; m < MAX_MASK; ++m) {
        std::vector<int> D;
        for (int d = 0; d < n_digits; ++d) {
            if (m & (1 << d)) {
                D.push_back(d);
            }
        }
        int k = D.size();
        if (k == 0) continue; // Should not happen

        int64_t total_m = 0;

        for (int L = k; L <= len_n; ++L) {
            int64_t total_L = 0;

            int subsets = 1 << k; // Total subsets of D
            for (int s = 0; s < subsets; ++s) {
                std::vector<int> D_S;
                int set_bits = 0;
                for (int i = 0; i < k; ++i) {
                    if ((s & (1 << i)) == 0) { // Digit is in D_S
                        D_S.push_back(D[i]);
                    } else {
                        set_bits++;
                    }
                }

                int64_t N_S = count_numbers(D_S, L);
                if (N_S == 0) continue;

                int parity = set_bits % 2;
                if (parity % 2 == 0) { // Even number of elements in S
                    total_L = (total_L + N_S) % MOD;
                } else {
                    total_L = (total_L - N_S + MOD) % MOD;
                }
            }
            total_m = (total_m + total_L) % MOD;
        }
        freq[m] = total_m;
        total_numbers_total = (total_numbers_total + total_m) % MOD;
    }

    // Compute total pairs
    cpp_int total_pairs = total_numbers_total * (total_numbers_total - 1) / 2;

    // Compute total non-friend pairs
    cpp_int total_non_friend_pairs = 0;
    for (int m1 = 1; m1 < MAX_MASK; ++m1) {
        for (int m2 = m1; m2 < MAX_MASK; ++m2) {
            if ((m1 & m2) == 0) { // Disjoint digit sets
                cpp_int product;
                if (m1 == m2) {
                    cpp_int freq_m = freq[m1];
                    product = freq_m * (freq_m - 1) / 2;
                } else {
                    product = cpp_int(freq[m1]) * freq[m2];
                }
                total_non_friend_pairs += product;
            }
        }
    }

    // Compute friend pairs
    cpp_int f_n = total_pairs - total_non_friend_pairs;

    // Compute result modulo MOD
    int64_t result = static_cast<int64_t>((f_n % MOD + MOD) % MOD);
    std::cout << result << std::endl;

    return 0;
}
