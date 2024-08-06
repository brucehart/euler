#include <iostream>
#include <vector>

// Function to compute the Euler's Totient function values for all integers up to a given limit
long long computeTotients(int limit) {
    // Create a vector to store the totient values, initialized to the index values
    std::vector<int> phi(limit + 1);
    for (int i = 0; i <= limit; ++i) {
        phi[i] = i; // Initialize phi[i] to i
    }

    // Use a sieve approach to compute the totient values
    for (int i = 2; i <= limit; ++i) {
        if (phi[i] == i) { // Check if i is a prime number
            for (int j = i; j <= limit; j += i) {
                // Update the totient value for all multiples of i
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }

    // Sum the totient values from 2 to the limit
    long long result = 0;
    for (int i = 2; i <= limit; ++i) {
        result += phi[i];
    }
    return result;
}

int main() {
    int limit = 1000000; // Define the limit for d
    long long totalReducedFractions = computeTotients(limit); // Compute the total number of reduced proper fractions
    std::cout << totalReducedFractions << std::endl;
    return 0;
}
