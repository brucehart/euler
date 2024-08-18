#include <iostream>

long long factorialMod(long long n);

// Function to compute (base^exponent) % mod efficiently
long long modPow(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Counts the number of factors of `factor` in the set {1, 2, ..., end}
long long countFactors(long long end, long long factor) {
    if (end == 0) {
        return 0;
    } else {
        return end / factor + countFactors(end / factor, factor);
    }
}

// Computes the product of all numbers from 1 to n that are coprime with 10, modulo 10^5
long long factorialCoprime(long long n) {
    n %= 100000;
    long long product = 1;
    for (long long i = 1; i <= n; i++) {
        if (i % 2 != 0 && i % 5 != 0) {
            product = i * product % 100000;
        }
    }
    return product;
}

// Computes the product of all odd numbers from 1 to n, with factors of 2 and 5 removed, modulo 10^5
long long oddFactorialMod(long long n) {
    if (n == 0) {
        return 1;
    } else {
        return oddFactorialMod(n / 5) * factorialCoprime(n) % 100000;
    }
}

// Computes the product of all even numbers from 1 to n, with factors of 2 and 5 removed, modulo 10^5
long long evenFactorialMod(long long n) {
    if (n == 0) {
        return 1;
    } else {
        return factorialMod(n / 2);
    }
}

// Computes n! modulo 10^5, with all factors of 2 and 5 removed
long long factorialMod(long long n) {
    return evenFactorialMod(n) * oddFactorialMod(n) % 100000;
}

// Returns the last 5 digits of n!, excluding trailing zeros
long long factorialSuffix(long long n) {
    long long twos = countFactors(n, 2) - countFactors(n, 5); // Number of 2's minus number of 5's
    // Reducing the number of twos based on a specific modulus cycle
    if (twos >= 2505) {
        twos = (twos - 5) % 2500 + 5;
    }
    // Compute the factorial mod 10^5 without trailing zeros
    return factorialMod(n) * modPow(2, twos, 100000) % 100000;
}

int main() {
    // Compute the last 5 digits of 10^12 factorial, excluding trailing zeros
    long long result = factorialSuffix(1000000000000LL);
    std::cout << result << std::endl;
    return 0;
}

