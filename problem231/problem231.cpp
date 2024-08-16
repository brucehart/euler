#include <iostream>
#include <vector>
#include <string>

const int MAX_N = 20000000;
const int MAX_K = 15000000;

std::vector<int> generateSmallestPrimeFactors(int limit) {
    std::vector<int> smallestPrimeFactor(limit + 1, 0);
    for (int i = 2; i <= limit; i++) {
        if (smallestPrimeFactor[i] == 0) { // i is a prime number
            for (int j = i; j <= limit; j += i) {
                if (smallestPrimeFactor[j] == 0) {
                    smallestPrimeFactor[j] = i;
                }
            }
        }
    }
    return smallestPrimeFactor;
}

long long sumFactorialPrimeFactors(int n, const std::vector<int>& smallestPrimeFactor) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int num = i;
        while (num > 1) {
            int primeFactor = smallestPrimeFactor[num];
            sum += primeFactor;
            num /= primeFactor;
        }
    }
    return sum;
}

int main() {
    std::vector<int> smallestPrimeFactors = generateSmallestPrimeFactors(MAX_N);

    // Calculate the sum of prime factors for the given factorial ranges
    long long result = sumFactorialPrimeFactors(MAX_N, smallestPrimeFactors)
                     - sumFactorialPrimeFactors(MAX_K, smallestPrimeFactors)
                     - sumFactorialPrimeFactors(MAX_N - MAX_K, smallestPrimeFactors);
    
    std::cout << result << std::endl;
    return 0;
}
