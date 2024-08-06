#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

// Function to generate primes using the Sieve of Eratosthenes
std::vector<int> generatePrimes(int max) {
    std::vector<bool> is_prime(max + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= max; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max; j += i) {
                is_prime[j] = false;
            }
        }
    }
    std::vector<int> primes;
    for (int i = 2; i <= max; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main() {
    const long long LIMIT = 50000000;
    const int maxPrime = 7072; // Since 7072^2 < 50,000,000

    std::vector<int> primes = generatePrimes(maxPrime);
    
    std::vector<long long> primeSquares;
    std::vector<long long> primeCubes;
    std::vector<long long> primeFourthPowers;

    // Calculate prime squares, cubes, and fourth powers
    for (int prime : primes) {
        long long p2 = static_cast<long long>(prime) * prime;
        if (p2 < LIMIT) primeSquares.push_back(p2);

        long long p3 = p2 * prime;
        if (p3 < LIMIT) primeCubes.push_back(p3);

        long long p4 = p3 * prime;
        if (p4 < LIMIT) primeFourthPowers.push_back(p4);
    }

    // Sort the fourth powers for efficient breaking in the inner loop
    std::sort(primeFourthPowers.begin(), primeFourthPowers.end());

    std::set<long long> results;

    // Find all sums of prime squares, cubes, and fourth powers
    for (long long p2 : primeSquares) {
        for (long long p3 : primeCubes) {
            if (p2 + p3 >= LIMIT) break;
            for (long long p4 : primeFourthPowers) {
                long long sum = p2 + p3 + p4;
                if (sum < LIMIT) {
                    results.insert(sum);
                } else {
                    break; // As primeFourthPowers is sorted, no need to check further
                }
            }
        }
    }

    std::cout << results.size() << std::endl;

    return 0;
}
