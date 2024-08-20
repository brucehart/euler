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
long long compute_sum(long long r_factor) {    
    std::vector<long long> primes = generate_prime_list(100000);
    long long sum = 5;

    for (long long x : primes) {
        if (x < 5) continue;

        if (modular_exponentiation(10, r_factor, x) != 1) {
            sum += x;
        }
    }
    
    return sum;
}

int main() {
    unsigned long long r_factor = std::pow(10, 18);
    std::cout << compute_sum(r_factor) << std::endl;
    return 0;
}
