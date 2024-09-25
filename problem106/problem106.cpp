#include <iostream>
#include <map>
#include <set>
#include <bitset>

int countSets(std::set<int>& bitset){
    int count = 0;

    for (int i = 0; i < bitset.size(); i++)
    {
        for (int j = i + 1; j < bitset.size(); j++)
        {           
            int a = *std::next(bitset.begin(), i);
            int b = *std::next(bitset.begin(), j);

            if (a&b != 0) continue;

            while (a > 0)
            {
                if ((~a & (a-1)) > (~b & (b-1)))
                {
                    count++;
                    std::cout << "a: " << std::bitset<12>(a) << " b: " << std::bitset<12>(b) << std::endl;
                    break;                    
                }

                a &= a - 1;
                b &= b - 1;
            }

        }
    }

    return count;
}

int main(){
    static const int N = 12;
    std::map<int, std::set<int>> bitsets;
    int count = 0;

    for (int j = 0; j < 12; j++)
    {
        bitsets[j] = std::set<int>();
    }

    for(int i = 0; i < (1 << N); i++){                
        int numBits = __builtin_popcount(i);
        bitsets[numBits].insert(i);
    }

    for (int k = 2; k < 11; k++)
    {
        count += countSets(bitsets[k]);
        std::cout << "k = " << k << " count = " << count << std::endl;
    }

    std::cout << count << std::endl;

    return 0;
}