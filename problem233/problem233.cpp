#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

//Reference: https://mathworld.wolfram.com/SumofSquaresFunction.html


// Sieve of Eratosthenes to generate primes up to a limit
std::vector<int> generatePrimes(int limit) {
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Integer square root
long long isqrt(long long n) {
    return static_cast<long long>(std::sqrt(n));
}

int main() {
    const long long N = 100000000000;
    
    // Generate primes up to a specified limit
    int prime_limit = N / (5 * 5 * 13 * 13) + 1;
    std::vector<int> primes = generatePrimes(prime_limit);

    // Separate primes into p % 4 == 1 and p % 4 == 3
    std::vector<int> primes_4k1, primes_4k3;
    for (int p : primes) {
        if (p % 4 == 1) {
            primes_4k1.push_back(p);
        } else {
            primes_4k3.push_back(p);
        }
    }

    int len_c = N / (5 * 5 * 13 * 13 * 17) + 1;
    std::vector<bool> choices(len_c, false);
    choices[1] = true;

    // Process primes % 4 == 3
    for (int p : primes_4k3) {
        if (p >= len_c) break;
        choices[p] = true;
    }

    for (int i = 3; i < len_c; i += 2) {
        if (choices[i]) continue;
        int l = isqrt(i);
        for (int p : primes) {
            if (p > l) break;
            if (i % p == 0) {
                if (p % 4 == 3) {
                    choices[i] = choices[i / p];
                }
                break;
            }
        }
    }

    for (int i = 1; i < (len_c + 1) / 2; ++i) {
        choices[i * 2] = choices[i];
    }

    std::vector<long long> cumulative_sum(len_c, 0);
    long long sum = 0;
    for (int i = 1; i < len_c; ++i) {
        if (choices[i]) sum += i;
        cumulative_sum[i] = sum;
    }

    long long total_sum = 0;
    long long Ndd = N / (5 * 5 * 13);
    long long Nd5 = N / 5;

    // Process combinations of primes % 4 == 1
    for (int p1 : primes_4k1) {
        long long k1 = static_cast<long long>(p1) * p1 * p1;
        if (k1 > Ndd) break;
        for (int p2 : primes_4k1) {
            if (p2 == p1) continue;
            long long k2 = k1 * p2 * p2;
            if (k2 > Nd5) break;
            for (int p3 : primes_4k1) {
                if (p3 == p1 || p3 == p2) continue;
                long long k3 = k2 * p3;
                if (k3 > N) break;
                total_sum += k3 * cumulative_sum[N / k3];
            }
        }
    }

    for (int p1 : primes_4k1) {
        long long k1 = static_cast<long long>(p1) * p1 * p1 * p1 * p1 * p1 * p1;
        if (k1 > Nd5) break;
        for (int p2 : primes_4k1) {
            if (p2 == p1) continue;
            long long k2 = k1 * p2 * p2 * p2;
            if (k2 > N) break;
            total_sum += k2 * cumulative_sum[N / k2];
        }
    }

    for (int p1 : primes_4k1) {
        long long k1 = static_cast<long long>(p1) * p1 * p1 * p1 * p1 * p1 * p1 * p1 * p1 * p1;
        if (k1 > Nd5) break;
        for (int p2 : primes_4k1) {
            if (p2 == p1) continue;
            long long k2 = k1 * p2 * p2;
            if (k2 > N) break;
            total_sum += k2 * cumulative_sum[N / k2];
        }
    }

    std::cout << total_sum << std::endl;
    
    return 0;
}
