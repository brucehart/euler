#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;  // Use multiprecision integers for large sums

// Basic primality test for small numbers
// This function checks whether a number `n` is prime
bool isPrime(int n) {
    if (n <= 1) return false;  // Numbers less than or equal to 1 are not prime
    if (n == 2 || n == 3) return true;  // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return false;  // Even numbers and multiples of 3 are not prime

    // For numbers greater than 3, check for divisibility starting from 5
    // and skip numbers that are multiples of 2 or 3 by incrementing in steps of 6
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;  // Divisible by `i` or `i+2` means not prime
    }
    return true;  // If no divisors found, `n` is prime
}

// Generate all prime numbers less than `n` using the `isPrime` function
std::vector<int> generatePrimes(int n) {
    std::vector<int> primes;
    for (int i = 2; primes.size() < n; i++) {  // Start from 2, the smallest prime
        if (isPrime(i)) {  // If `i` is prime
            primes.push_back(i);  // Insert the prime into the vector
        }
    }
    return primes;  // Return the list of generated primes
}

int main(){
    cpp_int max_sum = 0;  // Variable to store the maximum sum using multiprecision integers for large values
    auto primeList = generatePrimes(7001);  // Generate the first 7001 primes and store in primeList
    std::vector<int> a(primeList[7000], 6999);  // Initialize vector `a` with 7000th prime, size 6999
    
    std::vector<int> primeDiff(primeList.size() - 1, 0);  // Vector to store differences between consecutive primes
    int minDiffIdx = 0;  // Index of the smallest difference
    double minDiff = 0.0;  // Smallest difference value
    int sTerm = 0;  // Step term for adjustments in `a`

    // Calculate differences between consecutive primes
    for (int i = 0; i < primeList.size() - 1; i++) {
        primeDiff[i] = primeList[i + 1] - primeList[i];
    }

    // Calculate the initial sum of vector `a`
    auto sum_a = std::accumulate(a.begin(), a.end(), 0);

    // Adjust the sum of `a` to be divisible by 7000
    while (sum_a % 7000 != 0) {
        minDiffIdx = 0;  // Reset index of minimum difference
        minDiff = 99999999.0;  // Set a large initial minimum difference
        sTerm = 1;  // Default step term

        std::set<int> aValues(a.begin(), a.end());  // Create a set from `a` for faster lookup

        // Iterate over potential step values `s`
        for (int s = 1; s <= (sum_a % 7000); s++) {
            for (auto p : aValues) {  // Check each value `p` in `a`
                if (p - s < 0)  // Skip if subtracting `s` results in a negative value
                    continue;

                // Calculate difference ratio and check if it's the smallest
                if ((primeList[p] - primeList[p - s]) / double(s) < minDiff) {
                    minDiff = (primeList[p] - primeList[p - s]) / (2 * double(s));  // Update minimum difference
                    minDiffIdx = p;  // Store the index of the smallest difference
                    sTerm = s;  // Update the step term
                }
            }
        }

        // Find the element in `a` with value `minDiffIdx` and subtract `sTerm` from it
        auto it = std::find(a.begin(), a.end(), minDiffIdx);
        if (it != a.end()) {
            *it -= sTerm;
        }

        sum_a -= sTerm;  // Update the sum of `a` after adjustment
    }

    // After adjusting `a`, calculate the maximum sum using corresponding primes
    for (int i = 0; i < a.size(); i++) {
        max_sum += primeList[a[i]];  // Add the prime corresponding to `a[i]`
    }

    std::cout << max_sum << std::endl;  // Output the result

    return 0;  // Exit the program
}
