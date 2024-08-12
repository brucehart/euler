#include <iostream>
#include <vector>
#include <cmath>

// Function to generate prime numbers up to a given limit using Sieve of Eratosthenes
std::vector<int> generatePrimes(int limit) {
    std::vector<bool> isPrime(limit + 1, true);
    std::vector<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    return primes;
}

// Function to count semiprimes less than n
int countSemiprimes(int n) {
    int limit = static_cast<int>(n/2);
    std::vector<int> primes = generatePrimes(limit);
    int count = 0;

    for (size_t i = 0; i < primes.size(); ++i) {
        for (size_t j = i; j < primes.size(); ++j) {
            long long product = static_cast<long long>(primes[i]) * primes[j];
            if (product < n) {
                ++count;
            } else {
                break; // No need to continue if the product exceeds n
            }
        }
    }

    return count;
}

int main() {
    int n = 100000000;
    int count = countSemiprimes(n);
    std::cout << count << std::endl;

    return 0;
}
