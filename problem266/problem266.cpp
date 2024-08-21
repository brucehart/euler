#include <iostream>
#include <vector>
#include <cmath>
#include <gmp.h>  // Include the GMP header

// Function to generate all primes less than or equal to n using the Sieve of Eratosthenes
std::vector<int> sieve_of_eratosthenes(int n) {
    std::vector<bool> is_prime(n + 1, true);
    std::vector<int> primes;

    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (int i = p * p; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }

    return primes;
}

// Function to display a progress bar in the terminal
void display_progress_bar(std::size_t current, std::size_t total) {
    int bar_width = 50;
    float progress = static_cast<float>(current) / static_cast<float>(total);

    std::cout << "[";
    int pos = static_cast<int>(bar_width * progress);
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) {
            std::cout << "=";
        } else if (i == pos) {
            std::cout << ">";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

// Function to find the largest divisor of p that does not exceed sqrt_p using GMP
void find_max_divisor(const std::vector<int>& primes, mpz_t sqrt_p, mpz_t& max_divisor) {
    mpz_t dp[10001];  // Adjust size if necessary
    for (int i = 0; i <= 10000; ++i) {
        mpz_init(dp[i]);
    }
    mpz_set_ui(dp[0], 1); // Base case: A divisor of 1 is always possible

    mpz_t temp, prod;
    mpz_inits(temp, prod, NULL);

    std::size_t primes_count = primes.size();

    for (std::size_t i = 0; i < primes_count; ++i) {
        bool break_outer_loop = false;

        // Display progress for the outer loop
        display_progress_bar(i + 1, primes_count);

        for (mpz_set_ui(temp, 10000); mpz_cmp_ui(temp, primes[i]) >= 0; mpz_sub_ui(temp, temp, 1)) {
            mpz_t current_index;
            mpz_init_set(current_index, temp);
            mpz_sub_ui(current_index, current_index, primes[i]);

            if (mpz_cmp_ui(dp[mpz_get_ui(current_index)], 0) != 0) {
                mpz_mul_ui(prod, dp[mpz_get_ui(current_index)], primes[i]);
                if (mpz_cmp(prod, sqrt_p) <= 0) {
                    mpz_set(dp[mpz_get_ui(temp)], prod);
                }
            }

            mpz_clear(current_index);
        }

        // Allow the prime to be used multiple times
        for (mpz_set_ui(temp, primes[i]); mpz_cmp(temp, sqrt_p) <= 0; mpz_add_ui(temp, temp, 1)) {
            mpz_t current_index;
            mpz_init_set(current_index, temp);
            mpz_sub_ui(current_index, current_index, primes[i]);

            if (mpz_cmp_ui(dp[mpz_get_ui(current_index)], 0) != 0) {
                mpz_mul_ui(prod, dp[mpz_get_ui(current_index)], primes[i]);
                if (mpz_cmp(prod, sqrt_p) <= 0) {
                    mpz_set(dp[mpz_get_ui(temp)], prod);
                } else {
                    break_outer_loop = true;
                    break;  // Exit the inner loop early if exceeding sqrt_p
                }
            }

            mpz_clear(current_index);
        }

        // If we need to break the outer loop, do so here
        if (break_outer_loop) {
            break;
        }
    }

    // End of progress bar
    std::cout << std::endl;

    for (int i = 0; i <= 10000; ++i) {
        if (mpz_cmp(max_divisor, dp[i]) < 0) {
            mpz_set(max_divisor, dp[i]);
        }
        mpz_clear(dp[i]);
    }

    mpz_clears(temp, prod, NULL);
}

int main() {
    const int LIMIT = 190;
    const char* MOD = "10000000000000000";

    // Step 1: Generate primes up to LIMIT
    std::vector<int> primes = sieve_of_eratosthenes(LIMIT);

    // Step 2: Compute the product of the primes using GMP
    mpz_t p, sqrt_p, max_divisor, mod;
    mpz_inits(p, sqrt_p, max_divisor, mod, NULL);
    mpz_set_ui(p, 1);

    for (std::size_t i = 0; i < primes.size(); ++i) {
        mpz_mul_ui(p, p, primes[i]);
    }

    // Step 3: Calculate the square root of p
    mpz_sqrt(sqrt_p, p);

    // Step 4: Initialize max_divisor and mod
    mpz_set_ui(max_divisor, 0);
    mpz_set_str(mod, MOD, 10);

    // Step 5: Find the largest divisor <= sqrt(p) using dynamic programming with GMP
    std::cout << "Calculating maximum divisor, please wait..." << std::endl;
    find_max_divisor(primes, sqrt_p, max_divisor);

    // Step 6: Print the maximum divisor modulo MOD
    mpz_mod(max_divisor, max_divisor, mod);
    std::cout << "PSR(p) mod " << MOD << " = " << mpz_get_str(NULL, 10, max_divisor) << std::endl;

    // Clean up
    mpz_clears(p, sqrt_p, max_divisor, mod, NULL);

    return 0;
}
