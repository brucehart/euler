//Author: Bruce Hart <bruce.hart@gmail.com>
//The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.
//Find the smallest cube for which exactly five permutations of its digits are cube.

#include <iostream>
#include <cstring>
#include <gmp.h>
#include <stdexcept>
#include <map>
#include <string>
#include <cstdint>
#include <algorithm>

#define BUF_SIZE    256

std::string cube_to_sorted_str(mpz_t* c)
{
    char buf[BUF_SIZE];

    if (mpz_sizeinbase(*c, 10U) > (BUF_SIZE-2))
        throw std::overflow_error("Error: Buffer size exceeded in cube_to_string.");

    mpz_get_str(buf, 10, *c);
    std::sort(buf, buf+strlen(buf));

    return std::string(buf);
}

int main(int argc, char** argv)
{
    std::map<std::string, int> cubes;
    std::map<std::string, mpz_t> smallestCube;
    mpz_t a, c;
    mpz_init(a);
    mpz_init(c);
        
    unsigned long int aa = 1;
    std::string cc;
    
    while (true)
    {
        mpz_set_ui(a, aa);
        mpz_pow_ui(c, a, 3U);
        cc = cube_to_sorted_str(&c);
        cubes[cc]++;
        
        if (smallestCube.count(cc) == 0)
        {
            mpz_init(smallestCube[cc]);
            mpz_set(smallestCube[cc],c);
        }
        else
            if (mpz_cmp(c, smallestCube[cc]) < 0)
                mpz_set(smallestCube[cc], c);

        if (cubes[cc] == 5)
        {
            gmp_printf("%Zd\n", smallestCube[cc]);
            break;
        }

        aa++;
    }
    
    return 0;

}