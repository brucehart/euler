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

bool boolXor(bool a, bool b)
{
    return (a || b) && !(a && b);
}

int main(){
    std::bitset<64> a, b, target, resultTest, bTest;
    std::set<uint64_t> bSolutions;
    

    a.reset();
    
    while (b.to_ullong() < 1000000000000000000ULL)
    {
        uint64_t result = 0;       
        int bit = 0;

        resultTest.reset();
        b.reset();
        target = (5 ^ xorProduct(a.to_ullong(), a.to_ullong()));
        std::cout << target << std::endl;
        
        b[0] = target[0];
        bit++;

        while (bit <= 63)
        {
            bTest = b.to_ullong();
            bTest[bit] = 1;

            for(int i = bit; i >= 0; i--)
            {               
                resultTest[bit] = boolXor(resultTest[bit], bTest[i]*bTest[bit-i]);                    
                
                if (i > 0)
                    resultTest[bit] = boolXor(resultTest[bit], a[i-1]*bTest[bit-i]);
            }

            if (resultTest[bit] == target[bit])            
            {
                std::cout << "resultTest[bit]: " << resultTest[bit] << ", target[bit]: " << target[bit] << std::endl;
                b = bTest.to_ullong();
            }

            std::cout << "bit: " << bit << ", b: " << std::hex << b.to_ullong() << std::dec << std::endl;
            bit++;
        }

        if (b.to_ullong() < 1000000000000000000ULL)
        {
            bSolutions.insert(b.to_ullong());
            std::cout << "a: " << a << ", b: " << b << std::endl;
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