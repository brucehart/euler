#include <iostream>
#include <gmpxx.h>
#include <unordered_map>
#include <functional>

// Custom hash function for mpz_class
struct mpz_class_hash {
    std::size_t operator()(const mpz_class& num) const {
        // Convert the mpz_class to a string and hash the string
        return std::hash<std::string>()(num.get_str());
    }
};

// Custom equality function for mpz_class
struct mpz_class_equal {
    bool operator()(const mpz_class& lhs, const mpz_class& rhs) const {
        // Compare two mpz_class values using GMP's mpz_cmp function
        return mpz_cmp(lhs.get_mpz_t(), rhs.get_mpz_t()) == 0;
    }
};

// Unordered map to store already computed values of f(n) to avoid redundant calculations
std::unordered_map<mpz_class, mpz_class, mpz_class_hash, mpz_class_equal> F;

mpz_class f(const mpz_class& n) {
    // Check if the value of f(n) is already computed and stored in the map
    if (F.find(n) != F.end()) {
        // If found, return the stored value
        return F[n];
    }

    mpz_class val;  // Variable to store the result of f(n)
    mpz_class half = n / 2;  // Compute n / 2

    // If n is odd (n % 2 != 0)
    if (n % 2 != 0) {
        // The recursive call to f(half) will compute f(n) for odd n
        val = f(half);
    } else {
        // If n is even, compute f(n) as the sum of f(half) and f(half - 1)
        mpz_class halfMinusOne = half - 1;
        val = f(half) + f(halfMinusOne);
    }

    // Store the computed value of f(n) in the map to use in future calls
    F[n] = val;
    return val;
}

int main() {
    // Initialize the map with base cases
    F[0] = 1;  // f(0) = 1
    F[1] = 1;  // f(1) = 1

    // Create the large number 10^25
    mpz_class n;
    mpz_ui_pow_ui(n.get_mpz_t(), 10, 25);

    // Calculate f(10^25)
    mpz_class result = f(n);

    // Print the result in decimal form
    std::cout << result.get_str() << std::endl;

    return 0;
}
