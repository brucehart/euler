#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
#include <set>
#include <gmp.h>  // Include for GMP library (likely for handling large numbers)
#include <map>

// Define the upper limit for the calculation
static const unsigned int N = 100000000; 
// Initialize the final sum
unsigned long long sum = 0;

// Vector to store the product of prime factors for each number up to N. Initialized to 1.
std::vector<unsigned int> product(N + 1, 1);
// Vector to track if a number's prime product equals itself. Initialized to false.
std::vector<bool> summed(N + 1, false);
// Counter for the number of 'summed' numbers
unsigned int sum_count = 0;
// Map to store the count of each prime encountered during factorization
std::map<unsigned int, unsigned int> prime_count;
// Map to track if all powers of a prime up to N have been processed
std::map<unsigned int, bool> prime_filled;

// Function to update remaining numbers based on a prime and its multiplicity
void updateRemaining(unsigned int p, unsigned int m) {
    // Iterate through multiples of the prime 'p' up to N
    for (int i = p; i <= N; i += p) {
        // Skip if the number has already been summed
        if (summed[i]) continue;

        // Check if 'p' is a new prime factor of 'i' 
        if ((i / product[i]) % p == 0) {
            // Update the product of prime factors for 'i'
            product[i] *= p;
        }

        // If the product of prime factors equals the number itself
        if (product[i] == i) {
            // Mark it as summed, increment the count, and add to the sum
            summed[i] = true;
            sum_count++;
            sum += m; 
        }
    }
}

// Function to get the prime factorization of a number
std::vector<unsigned int> primeFactorization(int n) {
    // Initialize a GMP integer to handle potentially large 'n'
    mpz_t n_mpz;
    // Vector to store the prime factors
    std::vector<unsigned int> primeFactors;

    // Initialize the GMP integer with the value of 'n'
    mpz_init_set_ui(n_mpz, n);
    // Check if 'n' is prime using a probabilistic primality test
    if (mpz_probab_prime_p(n_mpz, 15) > 0) {
        // If prime, add it to the prime factors and return
        primeFactors.push_back(n);
    }
    // Clear the GMP integer
    mpz_clear(n_mpz);

    // If prime factors were found (n was prime), return them
    if (primeFactors.size() > 0)
        return primeFactors;

    // Handle even prime factors (2)
    while (n % 2 == 0) {
        primeFactors.push_back(2);
        n /= 2;
    }

    // Check for odd prime factors up to the square root of 'n'
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            primeFactors.push_back(i);
            n /= i;
        }
    }

    // If 'n' is greater than 2 after the loop, it's a prime factor itself
    if (n > 2) {
        primeFactors.push_back(n);
    }

    return primeFactors;
}

int main() {
    // Initialize a variable to track the next prime (not used in the current code)
    unsigned int nextPrime = 1;
    // Mark 0 and 1 as 'summed' (they are not prime)
    summed[0] = true;
    summed[1] = true;

    // Iterate through numbers from 2 to N
    for (unsigned int m = 2; m <= N; m++) {
        // Get the prime factors of 'm'
        auto primes = primeFactorization(m);

        // Process each prime factor of 'm'
        for (auto p : primes) {
            // Skip if all powers of this prime have been processed
            if (prime_filled[p]) continue;

            // Increment the count of this prime
            prime_count[p]++;

            // Check if the next power of this prime exceeds N
            if (pow(p, prime_count[p]) >= N) {
                // If so, mark this prime as 'filled'
                prime_filled[p] = true;
            } else {
                // Otherwise, update remaining numbers based on this prime and its multiplicity
                updateRemaining(p, m);
            }
        }
    }

    // Print the final sum
    std::cout << sum << std::endl;

    return 0;
}