#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

class ProblemSet
{
public:

    uint64_t a;
    uint64_t b;
    uint64_t target;
    std::vector<std::vector<int>> xorBits;
    bool xorState[64];
    uint64_t foundBMask = 0ULL;

    const uint64_t MASK_FOUND_ALL = 0xFFFFFFFFFFFFFFFFULL;

    ProblemSet(uint64_t aVal, uint64_t targetVal, uint64_t bVal = 0): a(aVal), b(bVal), target(targetVal)
    {
        setupTarget();        
        setupEquations();
        
        removeDuplicates();
        solveEquations();
    }    

    void setupTarget(){ target = target ^ xorProduct(a, a); std::cout << "Target: " << target << std::endl; }    
    void foundB(int bit){ foundBMask |= (1ULL << bit); }

    static const bool getBit(const uint64_t x, const int i) { 
        if (i > 63) return false;
        return (x & (1ULL << i)) != 0; 
    }

    static const uint64_t xorProduct(const uint64_t a, const uint64_t b)
    {
        uint64_t result = 0;
        for (int i = 0; i < 64; i++)
        {
            if (getBit(b, i))
                result ^= (a << i);
        }
        return result;
    }
    
    void setupEquations()
    {
        xorBits = std::vector<std::vector<int>>(64);
        
        for (int i = 0; i < 64; i++)
        {
            xorState[i] = false;                
            xorBits[i] = std::vector<int>();         
            
            if (i % 2 == 0)
                xorBits[i].push_back(i/2);       

            for (int k=(i-1);k<=0;k++)
            {
                if (i == 0) continue;
                if (getBit(a, k))
                {                  
                    xorBits[i].push_back(i-k-1);
                }
            }           
        }
        
        for (int j = 0; j < 64; j++)
        {
            std::cout << "xorBits[" << j << "]: ";
            for (const auto& elem : xorBits[j])
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
       
        std::cout << std::endl;
    }

    void removeDuplicates()
    {
        for (auto xB: xorBits)
        {            
            auto it = std::unique(xB.begin(), xB.end(), [](int a, int b) {
                return a == b;
            });
            xB.erase(it, xB.end());
        }
    }

    void solveEquations()
    {
        bool madeProgress = false;

        do
        {
            madeProgress = false;

            for (int i = 0; i < 64; i++)
            {        
                if (xorBits[i].size() == 1)
                {
                    int bit = xorBits[i][0];
                    
                    if (getBit(target, bit) ^ xorState[bit])
                    {
                        b |= (1ULL << bit);                     
                        for (int k = 0; k < 64; k++)
                        {
                            if (k != i && std::find(xorBits[k].begin(), xorBits[k].end(), bit) != xorBits[k].end())
                            {
                                xorState[k] = !xorState[k];
                            }
                        }
                    }

                    std::cout << "Set b[" << bit << "] = " << getBit(b, bit) << std::endl;

                    foundB(bit);
                    madeProgress = true;
                    xorBits[i].clear();

                    for (int j = 0; j < 64; j++)
                    {                        
                        xorBits[j].erase(std::remove(xorBits[j].begin(), xorBits[j].end(), bit), xorBits[j].end());
                    }
                }
            }
        } while (madeProgress && foundBMask != MASK_FOUND_ALL);

        if (foundBMask != MASK_FOUND_ALL)
            {
                std::cout << "No solution found | b = ";
                for (int i = 63; i >= 0; --i)
                {
                    std::cout << ((b >> i) & 1);
                }
                std::cout << std::endl;
            }

    }


};




int main()
{
    ProblemSet p1(6, 5);

    std::cout << "a: " << p1.a << " b: " << p1.b << " target: " << p1.target << std::endl;
    return 0;
}
