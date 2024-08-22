#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for std::gcd


// Function to compute the radical of a number
long long rad(int n, const std::vector<int>& smallest_prime) {
    long long result = 1;
    while (n > 1) {
        int p = smallest_prime[n];
        result *= p;
        while (n % p == 0) {
            n /= p;
        }
    }
    return result;
}

// Function to precompute the smallest prime factors
std::vector<int> sieve(int max_n) {
    std::vector<int> smallest_prime(max_n + 1, 0);
    for (int i = 2; i <= max_n; ++i) {
        if (smallest_prime[i] == 0) { // i is prime
            for (int j = i; j <= max_n; j += i) {
                if (smallest_prime[j] == 0) {
                    smallest_prime[j] = i;
                }
            }
        }
    }
    return smallest_prime;
}

int main() {
    const int LIMIT = 120000;
    unsigned long long sum_c = 0;

    // Precompute smallest prime factors and radicals
    auto smallest_prime = sieve(LIMIT);
    std::vector<long long> rad_values(LIMIT + 1, 0);
    for (int i = 1; i <= LIMIT; ++i) {
        rad_values[i] = rad(i, smallest_prime);
    }

    // Iterate over possible values of c
    for (int c = 2; c < LIMIT; ++c) {        
        for (int a = 1; a < c / 2; ++a) {
            int b = c - a;
            if (rad_values[a] * rad_values[b] * rad_values[c] < c) {
                if (std::gcd(rad_values[a], rad_values[b]) == 1) {                
                    sum_c += c;                    
                }
            }
        }
    }
    
    std::cout << sum_c << std::endl;

    return 0;
}
