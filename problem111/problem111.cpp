#include <iostream>
#include <gmp.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>

// Function to check primality using GMP's mpz_probab_prime_p
// Returns true if n is prime or probably prime based on the given number of iterations
bool is_probably_prime(long long n, int iterations = 15) {
    mpz_t num;              // Declare a GMP integer variable
    mpz_init(num);          // Initialize the GMP integer

    // Set the GMP integer to the value of n
    mpz_set_si(num, n);

    // Perform the probabilistic primality test using mpz_probab_prime_p
    int result = mpz_probab_prime_p(num, iterations);

    // Clear the GMP integer to free memory
    mpz_clear(num);

    // Return true if the result is prime or probably prime
    return result > 0;
}

// Function to find primes that include repeated digits
// repeated_digit: the digit to repeat in the number
// repeat_count: how many times the repeated_digit appears
// remaining_digits: number of remaining digits to generate
std::set<unsigned long long> repeated_digit_primes(int repeated_digit, int repeat_count, int remaining_digits) {
    std::set<unsigned long long> primes;   // Store primes found
    std::set<unsigned long long> checked;  // Store non-prime numbers to avoid rechecking

    // Loop through all possible combinations of remaining digits (0 to 10^remaining_digits)
    for (unsigned long long i = 0; i < pow(10, remaining_digits); i++) {
        std::vector<char> number_chars;   // Vector to store the number characters

        // Convert i to a string and add its digits to the vector
        std::string i_str = std::to_string(i);

        // Skip numbers containing the repeated_digit
        if (i_str.find(std::to_string(repeated_digit)) != std::string::npos) {
            continue;
        }

        // Add the digits of i to the number_chars vector
        number_chars.insert(number_chars.end(), i_str.begin(), i_str.end());

        // Add the repeated digit 'repeat_count' times to the number_chars
        number_chars.insert(number_chars.end(), repeat_count, '0' + repeated_digit);

        // Add '0' characters until the total length of number_chars is repeat_count + remaining_digits
        while (number_chars.size() < repeat_count + remaining_digits) {
            number_chars.insert(number_chars.begin(), '0');
        }

        // Sort the number_chars to generate all unique permutations
        std::sort(number_chars.begin(), number_chars.end());

        // Generate all permutations of number_chars
        do {
            // Skip permutations that start with '0'
            if (number_chars[0] == '0') continue;

            // Convert the permutation to a string
            std::string num_str(number_chars.begin(), number_chars.end());

            // Convert the string to an unsigned long long number
            unsigned long long num = std::stoull(num_str);

            // Skip if the number has already been checked or is already in primes
            if (checked.find(num) != checked.end() || primes.find(num) != primes.end()) {
                continue;
            }

            // Check if the number is probably prime
            if (is_probably_prime(num)) {
                primes.insert(num);  // Add to primes if it is probably prime
            } else {
                checked.insert(num);  // Mark as checked if not prime
            }
        } while (std::next_permutation(number_chars.begin(), number_chars.end()));  // Get next permutation
    }

    return primes;
}

int main() {
    int d_max = 10;                 // Maximum number of digits to repeat
    int repeat_count;               // Number of times the repeated digit will appear
    unsigned long long S_sum = 0;   // Sum of all found primes
    std::set<unsigned long long> primes;

    // Loop over all digits from 0 to 9
    for (int d = 0; d <= 9; d++) {
        repeat_count = d_max - 1;  // Initialize repeat_count to d_max - 1

        // Loop to reduce repeat_count and find primes
        while (true) {
            // Get primes with repeated digit 'd'
            primes = repeated_digit_primes(d, repeat_count, d_max - repeat_count);

            // If primes are found, sum them and break the loop
            if (!primes.empty()) {
                for (const auto& prime : primes) {
                    S_sum += prime;
                }
                break;
            }

            // Decrease repeat_count and try again
            repeat_count--;

            //Break out if no primes can be found with 2 or more repeated digits
            if (repeat_count < 2) {
                break;
            }
        }
    }

    // Output the sum of all found primes
    std::cout << S_sum << std::endl;

    return 0;
}
