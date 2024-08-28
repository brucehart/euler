#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <numeric>
#include <gmp.h> // Include GMP header for arbitrary precision arithmetic

// Function to generate primes using Sieve of Eratosthenes
std::vector<int> sieve(int limit) {
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to generate admissible numbers
void generate_admissible_numbers(int start, long long product, const std::vector<int>& primes, int limit, std::set<int>& admissible) {
    bool is_admissible = true;

    // If the product exceeds the limit, stop recursion
    if (product > limit) return;
    
    // Check if the product is admissible
    long long tmpProduct = product;
    for (int p: primes)
    {
        if (tmpProduct % p == 0)
        {
            // Remove all factors of p from tmpProduct
            while (tmpProduct % p == 0)                
                tmpProduct /= p;                
        }
        else if (tmpProduct > 1)
        {
            // If we encounter a prime that is not a factor of p before all prime factors are removed, it's not admissible
            is_admissible = false;
            break;
        }
    }

    // If admissible and greater than 1, add to the set
    if (is_admissible && product > 1) admissible.insert(product);
    
    // Recursively generate more admissible numbers
    for (int i = start; i < primes.size(); ++i) {
        if (product * primes[i] > limit) break;
        generate_admissible_numbers(i, product * primes[i], primes, limit, admissible);
    }
}

int main() {
    int limit = 1000000000; // 10^9
    std::vector<int> primes = sieve(23); // Generate primes up to 23
    std::set<int> admissible;

    // Generate admissible numbers starting with 2
    generate_admissible_numbers(0, 1, primes, limit, admissible);
    
    std::set<int> pseudo_fortunate_numbers;
    for (int n : admissible) {
        
        mpz_t mpz_n, mpz_prime;
        mpz_init_set_ui(mpz_n, n+1);
        mpz_init(mpz_prime);
        
        // Find the next prime after n+1
        mpz_nextprime(mpz_prime, mpz_n);
        int prime = mpz_get_ui(mpz_prime);
        
        // Calculate the pseudo-fortunate number
        int m = prime - n;        
        pseudo_fortunate_numbers.insert(m);
        
        // Clear GMP variables
        mpz_clear(mpz_n);
        mpz_clear(mpz_prime);
    }
    
    int sum = 0;
    
    // Calculate the sum of all unique pseudo-fortunate numbers
    sum = std::accumulate(pseudo_fortunate_numbers.begin(), pseudo_fortunate_numbers.end(), 0);  
    
    // Output the result
    std::cout << sum << std::endl;
    
    return 0;
}
