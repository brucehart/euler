#include <iostream>
#include <vector>
#include <bitset>

// Function to generate primes less than 100
std::vector<int> generate_primes() {
    std::vector<int> primes;
    std::bitset<100> is_prime;
    is_prime.set();  // Set all bits to true
    is_prime[0] = is_prime[1] = 0;  // 0 and 1 are not prime

    for (int i = 2; i < 100; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j < 100; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    return primes;
}

// Dynamic programming approach to count valid combinations
void count_combinations(const std::vector<int>& primes, long long N, int index, int count, long long current_product, long long& result) {
    if (current_product >= N) return;
    if (count >= 4) {
        result++;
    }

    for (int i = index; i < primes.size(); ++i) {
        // Include the current prime's value multiple times
        long long new_product = current_product;
        while (new_product < N / primes[i]) {
            new_product *= primes[i];
            count_combinations(primes, N, i + 1, count + 1, new_product, result);
        }
    }
}

int main() {
    const long long N = 1e16;
    std::vector<int> primes = generate_primes();

    long long result = 0;
    count_combinations(primes, N, 0, 0, 1, result);  // Start with a product of 1

    std::cout << "Number of integers less than 10^16 divisible by at least four distinct primes less than 100: " << result << std::endl;

    return 0;
}
