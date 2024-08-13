#include <iostream>
#include <vector>
#include <set>
#include <cmath>

const int MAX_LIMIT = 10000000;

// Generates a list of prime numbers up to the specified limit using the Sieve of Eratosthenes algorithm
std::vector<int> generatePrimes(int upperBound) {
    std::vector<bool> isPrime(upperBound + 1, true);
    std::vector<int> primes;

    for (int candidate = 2; candidate <= upperBound; candidate++) {
        if (isPrime[candidate]) {
            primes.push_back(candidate);
            for (int multiple = 2 * candidate; multiple <= upperBound; multiple += candidate) {
                isPrime[multiple] = false;
            }
        }
    }

    return primes;
}

int main() {
    std::set<int> validNumbers;  // Set to store all valid numbers that meet the criteria
    std::vector<int> primeList = generatePrimes(MAX_LIMIT / 2);

    int sqrtLimit = static_cast<int>(std::sqrt(MAX_LIMIT));

    // Loop through each pair of primes
    for (size_t i = 0; i < primeList.size(); i++) {
        int primeP = primeList[i];
        if (primeP > sqrtLimit)
            break;

        for (size_t j = i + 1; j < primeList.size(); j++) {
            int primeQ = primeList[j];
            int lcmPQ = primeP * primeQ;
            if (lcmPQ > MAX_LIMIT)
                break;

            int maxMultiplierLimit = MAX_LIMIT / lcmPQ;
            int currentMultiplier = 1;

            // Maximize the multiplier for primeP
            while (currentMultiplier * primeP <= maxMultiplierLimit)
                currentMultiplier *= primeP;

            int maxPrimeProduct = currentMultiplier;

            // Adjust the multiplier and include primeQ
            while (currentMultiplier % primeP == 0) {
                currentMultiplier /= primeP;
                while (currentMultiplier * primeQ <= maxMultiplierLimit)
                    currentMultiplier *= primeQ;
                maxPrimeProduct = std::max(currentMultiplier, maxPrimeProduct);
            }

            // Store the maximum product of primes multiplied by their least common multiple
            validNumbers.insert(maxPrimeProduct * lcmPQ);
        }
    }

    long long sumOfValidNumbers = 0;
    for (int validNumber : validNumbers)
        sumOfValidNumbers += validNumber;

    // Output the final sum of all valid numbers
    std::cout << sumOfValidNumbers << std::endl;

    return 0;
}
