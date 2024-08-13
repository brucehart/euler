#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <set>

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

// Function to precompute logarithms of powers of a given base up to the maximum exponent
std::vector<double> precomputeLogPowers(int base, int N) {
    std::vector<double> log_powers;
    int maxExponent = static_cast<int>(std::floor(std::log(N) / std::log(base)));

    for (int exponent = 1; exponent <= maxExponent; ++exponent) {
        log_powers.push_back(exponent * std::log(base));
    }

    return log_powers;
}

// Custom hash function for pairs of integers
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

// Cache structure for storing results of maximizeExpression
std::unordered_map<std::pair<int, int>, double, pair_hash> cache;

// Optimized function to maximize the sum of logs of p^a * q^b <= N using two-pointer technique
double maximizeExpression(int p, int q, double logN, int N) {
    // Check if result is already cached
    std::pair<int, int> prime_pair = std::make_pair(p, q);
    if (cache.find(prime_pair) != cache.end()) {
        return cache[prime_pair];
    }

    std::vector<double> log_p_powers = precomputeLogPowers(p, N);
    std::vector<double> log_q_powers = precomputeLogPowers(q, N);

    double max_sum_log = -1; // Initialize to an invalid value

    // Use two-pointer technique to find the maximum valid sum of log(p^a) + log(q^b) <= log(N)
    int i = 0;
    int j = log_q_powers.size() - 1;

    while (i < log_p_powers.size() && j >= 0) {
        double sum_log = log_p_powers[i] + log_q_powers[j];

        if (sum_log <= logN) {
            max_sum_log = std::max(max_sum_log, sum_log);
            i++;  // Move to the next power of p
        } else {
            j--;  // Decrease power of q
        }
    }

    // Cache the result before returning
    cache[prime_pair] = max_sum_log;
    return max_sum_log;
}

// Function to solve the problem
int solve(int N) {
    std::vector<int> primes = generatePrimes(N / 2);
    std::set<int> results;
    double logN = std::log(N);

    for (size_t i = 0; i < primes.size(); ++i) {
        
        if (i%10 == 0) std::cout << i << "/" << primes.size() << std::endl;

        for (size_t j = i + 1; j < primes.size(); ++j) {
            int p = primes[i];
            int q = primes[j];
            double max_log_value = maximizeExpression(p, q, logN, N);

            if (max_log_value >= 0) {
                int value = static_cast<int>(std::floor(std::exp(max_log_value)));
                if (value <= N) {
                    results.insert(value);
                }
            }
        }
    }

    int sum = 0;
    for (int value : results) {
        sum += value;
    }

    return sum;
}

int main() {
    int N = 10000000;
    int result = solve(N);
    std::cout << result << std::endl;
    return 0;
}
