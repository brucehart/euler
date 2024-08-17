#include <iostream>
#include <cmath>

bool is_progressive_square(long long n) {
    for (long long d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            long long q = n / d;
            for (long long r = 1; r < d; ++r) {
                if (q * r == d * r) { // Check the geometric sequence condition
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    long long limit = 1000000000000LL; // 10^12
    long long sum = 0;

    for (long long i = 1; i * i < limit; ++i) {
        if (i % 1000 == 0) std::cout << i << std::endl;

        long long square = i * i;
        if (is_progressive_square(square)) {
            sum += square;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}

