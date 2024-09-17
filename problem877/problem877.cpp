#include <iostream>
#include <cstdint>
#include <set>
#include <bitset>

class BitElement
{
public:
    std::bitset<64> bits;
    std::bitset<64> isSet;
    void setAll(uint64_t value) { bits = value; isSet = 0xFFFFFFFFFFFFFFFF;};
    void set(int bit, int value) { bits[bit] = value; isSet[bit] = 1; };
    char get(int bit) { return bits[bit]; };
    bool valueSet(int bit) { return isSet[bit]; };
    uint64_t value(){ return bits.to_ullong(); };
    BitElement(uint64_t value=0) : bits(value) {};    
}

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

char computeBProductBit(int bit, BitElement& aProduct, BitElement& midProduct, BitElement& target)
{    
    char result = aProduct.get(bit) ^ midProduct.get(bit);
    
    if (target.get(bit) == 1) return result == 1 ? 0 : 1;
    else return result;
}

void setMidProduct(int bit, BitElement& a, BitElement& b, BitElement& midProduct)
{
    char productBit = 0;

    for (int i = bit; i >= 0; i--)
    {
        if (a.get(i+1) == 1) productBit ^= b.get(i);
    }

    midProduct.set(bit, productBit);
}


int main(){
    BitElement a, b, aProduct, midProduct, target;
    std::set<uint64_t> bSolutions;

    a.setAll(0);
    b.setAll(0); 
    target.setAll(5);   
    
    while (b.value < 1000000000000000000ULL)
    {
        a.setAll(b.value);
        aProduct.setAll(xorProduct(a,a));

        int counter = 0;    
        midProduct.set(0,0);
        char bValue = computeBProductBit(counter, aProduct, midProduct, target);
        b.set(0, bValue);

        while (counter < 62)
        {
            counter++;
            setMidProduct(counter, a, b, midProduct);
            bValue = computeBProductBit(counter, aProduct, midProduct, target);
            b.set(counter, bValue);        
        }

        if (b.value < 1000000000000000000ULL)        
            bSolutions.insert(b.value); 

        std::cout << "a: " << a.value << ", b: " << b.value << std::endl;
    }
    
    uint64_t result = 0;
    
    for (auto it = bSolutions.begin(); it != bSolutions.end(); it++)
    {
        result ^= *it;
    }

    std::cout << result << std::endl;

    return 0;
}