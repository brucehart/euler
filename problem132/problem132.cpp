#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

// Function to generate a list of booleans indicating the primality of numbers up to n
std::vector<bool> generate_primality_list(long long n) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i <= std::sqrt(n); i++) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Function to generate a list of prime numbers up to n
std::vector<long long> generate_prime_list(long long n) {
    std::vector<bool> is_prime = generate_primality_list(n);
    std::vector<long long> primes;
    for (long long i = 0; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}


// Function to perform modular exponentiation
long long modular_exponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to compute the sum of potential prime factors meeting specific conditions
long long compute_sum(long long limit) {
    std::vector<long long> potential_factors;
    std::vector<long long> primes = generate_prime_list(1000000);

    for (long long x : primes) {
        if (modular_exponentiation(10, 1000000000, 9 * x) == 1) {
            potential_factors.push_back(x);
        }
    }

    long long total = 0;
    for (size_t i = 0; i < std::min(limit, (long long)potential_factors.size()); i++) {
        total += potential_factors[i];
    }

    return total;
}

int main() {
    std::cout << compute_sum(40) << std::endl;
    return 0;
}
