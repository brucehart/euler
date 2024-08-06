#include <iostream>
#include <vector>

const int LIMIT = 5000; // Set a limit for the maximum number to check

std::vector<int> generatePrimes(int limit) {
    std::vector<bool> is_prime(limit + 1, true);
    std::vector<int> primes;
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

int main() {
    std::vector<int> primes = generatePrimes(LIMIT);
    std::vector<int> ways(LIMIT + 1, 0);
    ways[0] = 1; // Base case: there is one way to write 0 as a sum of primes (using no primes at all)

    for (int prime : primes) {
        for (int j = prime; j <= LIMIT; ++j) {
            ways[j] += ways[j - prime];
        }
    }

    for (int i = 0; i <= LIMIT; ++i) {
        if (ways[i] > 5000) {
            std::cout << i << std::endl;
            break;
        }
    }

    return 0;
}