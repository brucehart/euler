#include <iostream>
#include <vector>
#include <cmath>

// Function to generate a list of primes up to a given limit
std::vector<bool> generate_prime_list(int limit) {
    std::vector<bool> primelist(limit + 1, true);
    primelist[0] = primelist[1] = false;

    for (int i = 2; i * i <= limit; ++i) {
        if (primelist[i]) {
            for (int j = i * i; j <= limit; j += i) {
                primelist[j] = false;
            }
        }
    }
    return primelist;
}

// Function to check if all divisors of n have the property that d + n/d is prime
bool check_divisors(const std::vector<bool>& primelist, int n) {
    int sqrt_n = static_cast<int>(std::sqrt(n));
    for (int d = 1; d <= sqrt_n; ++d) {
        if (n % d == 0) {
            int div_sum = d + n / d;
            if (div_sum >= primelist.size() || !primelist[div_sum]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    const int limit = 100000000;
    const int divisor_condition = 4;
    const int addend = 2;

    // Generate the prime list up to limit
    std::vector<bool> primelist = generate_prime_list(limit);

    long long sum = 1; //start with the case n=1

    // Generate values list where n = 4k + 2
    for (int n = addend; n <= limit; n += divisor_condition) {
        if (primelist[n + 1]) {
            if (check_divisors(primelist, n)) {
                sum += n;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
