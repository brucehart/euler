#include <iostream>
#include <cstdint>
#include <set>
#include <bitset>

uint64_t xorProduct(uint64_t x, uint64_t y)
{
    uint64_t res = 0;
    for (uint64_t i = 0; i < 64; i++)
    {
        if ((x & (1ULL << i)) != 0)
        {
            for (uint64_t j = 0; j < 64; j++)
            {
                if ((y & (1ULL << j)) != 0)
                {
                    res ^= (1ULL << (i + j));
                }
            }
        }
    }
    return res;
}



int main(){
    uint64_t a, b, result;
    std::set<uint64_t> bSolutions;
    a = 0;
    b = 0;
    result = 0;


    while(b < 100000000000000000ULL)
    {
        result = xorProduct(a,a);
        result ^= (xorProduct(a,b) << 1);
        result ^= xorProduct(b,b);

        if (result == 5)
        {
            std::cout << "a: " << a << ", b: " << b << std::endl;            
            bSolutions.insert(b);
            a = b;
            b++;
            
        }
        else 
            b++;

    }

    result = 0;
    for (auto it = bSolutions.begin(); it != bSolutions.end(); it++)
    {
        result ^= *it;
    }

    std::cout << result << std::endl;

    return 0;
}