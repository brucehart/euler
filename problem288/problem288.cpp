#include <iostream>
#include <cstdint>
#include <gmpxx.h>  // Include this header for mpz_class

// Constants used in the problem
const int BASE = 61;
const int64_t LIMIT = 10000000;
const int EXP_LIMIT = 10;
mpz_class MODULO;

// Function to calculate (base^exponent) % modulus using GMP
mpz_class mod_exp(int64_t base, int64_t exponent, const mpz_class& modulus) {
    mpz_class result;
    mpz_powm_ui(result.get_mpz_t(), mpz_class(base).get_mpz_t(), exponent, modulus.get_mpz_t());
    return result;
}

// Function to compute the sum of BASE^(n-1) modulo MODULO iteratively
mpz_class sum_of_powers_iterative(int64_t n) {
    mpz_class sum = 0;
    mpz_class current_power = 1;

    for (int64_t i = 0; i < n; ++i) {
        sum += current_power;
        current_power = (current_power * BASE) % MODULO;
    }

    return sum;
}

// Main function to solve the problem
int64_t compute_sum() {
    int64_t current_value = 290797; // Initial seed value
    mpz_class total_sum = 0;        // To store the final sum
    mpz_class current_power_sum = 0; // To store the sum of powers

    // Loop through all values from 0 to LIMIT
    for (int64_t n = 0; n <= LIMIT; ++n) {
        int64_t remainder = current_value % BASE; // Calculate the remainder
        current_value = mod_exp(current_value, 2, 50515093).get_si(); // Update current_value with (current_value^2) % 50515093

        // Compute the sum of powers for values of n less than or equal to EXP_LIMIT
        if (n <= EXP_LIMIT) {
            current_power_sum = sum_of_powers_iterative(n);
        }

        // Update the total sum
        total_sum += current_power_sum * remainder;
        total_sum %= MODULO;
    }

    // Return the result as a 64-bit integer
    return total_sum.get_si();
}

int main() {
    // Calculate the precise value of MODULO
    MODULO = 1;
    for (int i = 0; i < EXP_LIMIT; ++i) {
        MODULO *= BASE;
    }

    // Output the result of the computation
    std::cout << compute_sum() << std::endl;
    return 0;
}

