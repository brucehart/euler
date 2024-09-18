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
            for (uint64_t j = 0; j < 64-i; j++)
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
    std::bitset<64> a, b, target, resultTest, bTest;
    std::set<uint64_t> bSolutions;
    int bit = 0;

    a.reset();

    while (b.to_ullong() < 1000000000000000000ULL)
    {
        uint64_t result = 0;
        

        b.reset();
        target = (5 ^ xorProduct(a.to_ullong(), a.to_ullong()));
        
        b[0] = target[0];
        bit++;

        while (bit <= 63)
        {
            bTest = b.to_ullong();
            bTest[bit] = 1;

            for(int i = bit; i >= 0; i--)
            {             
                
                resultTest[bit] ^= bTest[i]*bTest[bit-i];                    
                
                if (i > 0)
                    resultTest[bit] ^= a[i-1]*bTest[bit-i];
            }

            if (resultTest[bit] == target[bit])            
            {
                b = bTest.to_ullong();
            }
        }

        if (b.to_ullong() < 1000000000000000000ULL)
        {
            bSolutions.insert(b.to_ullong());
        }

        a = b.to_ullong();                       
    }
    
    uint64_t result = 0;
    
    for (auto it = bSolutions.begin(); it != bSolutions.end(); it++)
    {
        result ^= *it;
    }

    std::cout << result << std::endl;

    return 0;
}