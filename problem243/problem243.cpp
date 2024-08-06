#include <iostream>
#include <vector>
#include <numeric>

// Function to generate primes up to max_n using the Sieve of Eratosthenes
std::vector<long long> sieve(long long max_n) {
    std::vector<bool> is_prime(max_n + 1, true);
    std::vector<long long> primes;
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i <= max_n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = i * i; j <= max_n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

// Function to calculate Euler's totient function using prime factors
long long totient(long long n, const std::vector<long long>& primes) {
    long long result = n;
    for (long long p : primes) {
        if (p * p > n) break;
        if (n % p == 0) {
            result -= result / p;
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

int main() {
    const double target_resilience = 15499.0 / 94744.0;
    const long long max_prime = 100;  // Adjust this value to search more primes

    // Generate primes
    auto primes = sieve(max_prime);

    // Multiply sequential primes and calculate resilience
    long long product = 1;
    double resilience = 1.0;
    int prime_index = 0;

    // Step 1: Multiply sequential primes until the ratio is exceeded
    while (resilience >= target_resilience && prime_index < primes.size()) {
        product *= primes[prime_index];
        long long phi_product = totient(product, primes);
        resilience = static_cast<double>(phi_product) / (product - 1);
        prime_index++;
    }

    // Step 2: Backtrack one step and try combinations of smaller primes
    product /= primes[prime_index - 1];
    prime_index--;
    

    // Try combinations of smaller primes and their products
    for (int i = 2; i <= 10; ++i) {
        long long new_product = product * i;
        long long phi_new_product = totient(new_product, primes);
        double new_resilience = static_cast<double>(phi_new_product) / (new_product - 1);
        if (new_resilience < target_resilience) {
            product = new_product;
            resilience = new_resilience;
            break;
        }
    }

    // Output the result
    std::cout << product << std::endl;

    return 0;
}
