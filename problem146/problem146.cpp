#include <iostream>
#include <set>
#include <gmp.h>

bool is_prime_gmp(mpz_t n) {
    // Use GMP's probabilistic prime test function
    // Returns > 0 if n is probably prime, 0 if n is definitely composite
    return mpz_probab_prime_p(n, 20) > 0;
}

// Function to check if a number is prime
bool is_prime(long long n) {
    // Handle edge cases
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Check for factors from 5 to sqrt(n)
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

bool verify_consecutive_primes(unsigned long long n, const std::set<int>& adders) {   
    for(int i = 1;i < *adders.rbegin();i++) {
        if (adders.find(i) == adders.end() && is_prime(n*n + i))
                return false;  
    }
    
    return true;
}

int main() {
    const unsigned long long N_MAX = 150000000;
    unsigned long long n = 10;
    unsigned long long sum = 0;
    const std::set<int> adders = {1, 3, 7, 9, 13, 27};

    mpz_t n2, n2_plus_a;
    mpz_init(n2);
    mpz_init(n2_plus_a);

    while (n < N_MAX) {
        // Calculate n^2
        mpz_set_ui(n2, n);
        mpz_mul(n2, n2, n2);

        bool non_prime = false;

        for (int a : adders) {
            // Calculate n^2 + a
            mpz_set_ui(n2_plus_a, a);
            mpz_add(n2_plus_a, n2, n2_plus_a);

            // Check if n^2 + a is prime
            if (!is_prime_gmp(n2_plus_a)) {
                non_prime = true;
                break;
            }
        }

        if (!non_prime && verify_consecutive_primes(n, adders))
                sum += n;                 

        n += 10;
    }

    std::cout << sum << std::endl;

    mpz_clear(n2);
    mpz_clear(n2_plus_a);

    return 0;
}
