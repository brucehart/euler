//Author: Bruce Hart <bruce.hart@gmail.com>

// The first known prime found to exceed one million digits was discovered in 1999, and is a Mersenne prime of the form 26972593−1; it contains exactly 2,098,960 digits. Subsequently other Mersenne primes, of the form 2p−1, have been found which contain more digits.
// However, in 2004 there was found a massive non-Mersenne prime which contains 2,357,207 digits: 28433×2^7830457+1.
// Find the last ten digits of this prime number.

#include <cstring>
#include <iostream>
#include <gmp.h>

int main(int argc, char** argv)
{
    mpz_t p;
    mpz_init(p);
    mpz_ui_pow_ui(p, 2, 7830457);
    mpz_mul_ui(p, p, 28433);
    mpz_add_ui(p, p, 1);

    char buf[2400000];
    mpz_get_str(buf, 10, p);
    
    char* c = buf;
    c+=strlen(buf) - 10;
    std::cout << c << std::endl;
}