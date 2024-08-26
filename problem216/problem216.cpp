#include <gmp.h>
#include <iostream>

int main() {
    const long long max_n = 50000000;
    int prime_count = 0;

    mpz_t t, n_square, temp;
    mpz_init(t);
    mpz_init(n_square);
    mpz_init(temp);

    for (long long n = 2; n <= max_n; ++n) {
        mpz_set_ui(temp, n);
        mpz_mul(n_square, temp, temp); // n_square = n^2
        mpz_mul_ui(t, n_square, 2); // t = 2 * n^2
        mpz_sub_ui(t, t, 1); // t = 2 * n^2 - 1

        if (mpz_probab_prime_p(t, 15) > 0) {
            ++prime_count;
        }      
    }

    std::cout << prime_count << std::endl;

    mpz_clear(t);
    mpz_clear(n_square);
    mpz_clear(temp);

    return 0;
}

