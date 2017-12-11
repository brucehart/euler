// Author: Bruce Hart <bruce.hart@gmail.com>

// The Fibonacci sequence is defined by the recurrence relation:

// Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

// It turns out that F541, which contains 113 digits, is the first Fibonacci number for which the last nine digits are 1-9 pandigital 
// (contain all the digits 1 to 9, but not necessarily in order). And F2749, which contains 575 digits, is the first Fibonacci number 
// for which the first nine digits are 1-9 pandigital.

// Given that Fk is the first Fibonacci number for which the first nine digits AND the last nine digits are 1-9 pandigital, find k.

//Note: Uses GMP library use "sudo apt install libgmp-dev libgmpxx4ldbl" to install on Ubuntu

#include <iostream>
#include <cstring>
#include <gmp.h>
#include <stdexcept>

#define BUF_SIZE    (100*1024)

void fib_next(mpz_t& n_1, mpz_t& n_2, mpz_t& f)
{   
    if (mpz_cmp_ui(n_1, 0) == 0)
        mpz_set_ui(f, 1);        
    else    
        mpz_add(f, n_1, n_2);    

    mpz_set(n_2, n_1);
    mpz_set(n_1, f);
}

bool pandigital(char* s)
{
    int b = 0;

    for (int i=0;i<9;i++)
    {
        if (s[i] < '1' || s[i] > '9') return false;
        b |= (1 << (s[i]-'1'));        
    }

    return (b == 511);
}

bool check_pandigital(mpz_t& n, char* buf)
{
    if (mpz_sizeinbase(n, 10) > (BUF_SIZE - 2))
        throw std::overflow_error("Error: Buffer size exceeded in check_pandigital().");

    mpz_get_str(buf, 10, n);    

    int w = strlen(buf);    
    if (w < 9) return false;

    return pandigital(buf) && pandigital(&buf[w-9]);
}

int main(int argc, char** argv)
{
    long n = 0;
    mpz_t n_1, n_2, f;
    mpz_init(n_1);
    mpz_init(n_2);
    mpz_init(f);

    char buf[BUF_SIZE];

    while(true)
    {
        n++;
        fib_next(n_1, n_2, f);
        
        if (check_pandigital(f, buf))
        {
            std::cout << n << "\n";
            break;
        }

    }

    return 0;

}