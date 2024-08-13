#include <iostream>
#include <vector>

// Function to generate all prime numbers up to n using the Sieve of Eratosthenes
std::vector<int> generatePrimes(int n) {
    std::vector<bool> is_prime(n + 1, true);
    std::vector<int> primes;

    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    return primes;
}

// Function to solve the problem using counting of prime factors
long long solve(int N) {
    std::vector<int> primes = generatePrimes(N/2);
    std::vector<int> count(N + 1, 0);

    // Increment counters for multiples of each prime
    for (int p : primes) {
        for (int multiple = p; multiple <= N; multiple += p) {
            count[multiple]++;
        }
    }

    // Sum values where the counter is exactly 2
    long long sum = 0;
    for (int i = 2; i <= N; ++i) {
        if (count[i] == 2) {
            sum += i;
        }
    }

    return sum;
}

int main() {
    int N = 10000000;  // Example for N = 10^7
    long long result = solve(N);
    std::cout << result << std::endl;
    return 0;
}
