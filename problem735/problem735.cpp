#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <utility>

// Function to compute the prime factorization of n
std::vector<std::pair<mpz_class, int>> prime_factorization(mpz_class n) {
    std::vector<std::pair<mpz_class, int>> factors;

    mpz_class divisor = 2;

    // Check for the number of 2s that divide n
    int count = 0;
    while (n % divisor == 0) {
        n /= divisor;
        count++;
    }
    if (count > 0) {
        factors.push_back({divisor, count});
    }

    // Check for odd divisors from 3 upwards
    for (divisor = 3; divisor * divisor <= n; divisor += 2) {
        count = 0;
        while (n % divisor == 0) {
            n /= divisor;
            count++;
        }
        if (count > 0) {
            factors.push_back({divisor, count});
        }

        // If n becomes 1, we can break early
        if (n == 1) {
            break;
        }
    }

    // If n is still greater than 1, then n itself is prime
    if (n > 1) {
        factors.push_back({n, 1});
    }

    return factors;
}

// Function to compute the number of divisors (sigma_0)
mpz_class sigma_0(const std::vector<std::pair<mpz_class, int>>& factors) {
    mpz_class result = 1;
    for (const auto& factor : factors) {
        int exponent = factor.second;
        result *= (exponent + 1);
    }
    return result;
}

// Function F(n) which computes (sigma_0(n^2) - 1) / 2
mpz_class F(mpz_class n) {
    // First, compute the prime factorization of n^2
    std::vector<std::pair<mpz_class, int>> factors = prime_factorization(n);

    // Multiply the exponents by 2 because we are considering n^2
    for (auto& factor : factors) {
        factor.second *= 2;
    }

    // Compute sigma_0 of n^2
    mpz_class sigma = sigma_0(factors);

    // Return (sigma_0(n^2) - 1) / 2
    return (sigma - 1) / 2;
}

// Function to print the result of F(n) to stdout
void print_F(mpz_class n) {
    mpz_class result = F(n);
    std::cout << "F(" << n << ") = " << result << std::endl;
}

// Function to compute the sum of F(n) from n=1 to n
mpz_class f_sum(mpz_class n) {
    mpz_class total_sum = 0;
    for (mpz_class i = 1; i <= n; i++) {
        total_sum += F(i);
    }
    return total_sum;
}

// Function to print the result of f_sum(n) to stdout
void print_f_sum(mpz_class n) {
    mpz_class result = f_sum(n);
    std::cout << "Sum of F(n) from 1 to " << n << " = " << result << std::endl;
}

int main() {
    mpz_class n("1000"); // Example small number for summing F(n) from 1 to n

    print_f_sum(n);

    return 0;
}
