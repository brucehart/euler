#include <iostream>
#include <vector>
#include <cmath>

// Function to generate prime numbers less than 100
std::vector<int> generate_primes(int limit) {
    std::vector<int> primes;
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }
    return primes;
}

// Recursive function to count valid Hamming numbers
void count_hamming_numbers(const std::vector<double>& logs, double current_sum, int index, int& count) {
    if (current_sum > 9.0) {
        return;
    }
    ++count;
    for (int i = index; i < logs.size(); ++i) {
        double next_sum = current_sum + logs[i];
        count_hamming_numbers(logs, next_sum, i, count); // Allow reusing the same prime
    }
}

int main() {
    // Generate primes less than 100
    std::vector<int> primes = generate_primes(100);

    // Calculate log10 of each prime
    std::vector<double> logs;
    for (int prime : primes) {
        logs.push_back(log10(prime));
    }

    // Counter for Hamming numbers
    int count = 0;

    // Start recursive counting from the first prime (index 0)
    count_hamming_numbers(logs, 0.0, 0, count);

    // Output the result
    std::cout << count << std::endl;

    return 0;
}
