#include <iostream>
#include <gmpxx.h>

typedef mpz_class ull;

ull g(const ull& N) {
    ull count = 0;
    ull max_y;
    mpz_class N_div_41 = N / 41;
    mpz_sqrt(max_y.get_mpz_t(), N_div_41.get_mpz_t());

    for (ull y = 1; y <= max_y; ++y) {
        ull y2 = y * y;
        ull term = N - 41 * y2;
        if (term > 0) {
            ull sqrt_term;
            mpz_sqrt(sqrt_term.get_mpz_t(), term.get_mpz_t());
            ull x_max = (sqrt_term - y) / 2;
            for (ull x = x_max; x >= 1; --x) {
                if (x * x + x * y + 41 * y2 < N) {
                    count += x;
                    break;
                }
            }
        }
    }
    return count;
}

int main() {
    ull N;
    mpz_ui_pow_ui(N.get_mpz_t(), 10, 16); // N = 10^16
    ull result = g(N);
    std::cout << "T(10^16) = " << result << std::endl;
    return 0;
}