#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <gmp.h>

static const int MAX_DIGITS = 14;

bool isPrime(unsigned long long num)
{
    mpz_t n;
    mpz_init(n);
    mpz_set_ui(n, num);

    int result = mpz_probab_prime_p(n, 25); // 25 is the number of Miller-Rabin iterations

    if (result > 0) {
        return true; // num is probably prime
    } else {
        return false; // num is definitely composite
    }

    mpz_clear(n);
}

unsigned long long sumDigits(unsigned long long num)
{
    unsigned long long sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void populateHarshad(std::map<unsigned long long, bool>& currentHarshad, std::map<unsigned long long, bool>& parentHarshad)
{
    parentHarshad = currentHarshad;
    currentHarshad.clear();
    
    for(auto it = parentHarshad.begin(); it != parentHarshad.end(); it++)
    {
        unsigned long long num = it->first;
        for(int i = 0; i < 10; i++)
        {
            unsigned long long newNum = num * 10 + i;
            auto s = sumDigits(newNum);           

            if((newNum % s) == 0)
            {              
                if (isPrime(newNum / s))                
                    currentHarshad[newNum] = true;    
                else
                    currentHarshad[newNum] = false;                                
            }
        }
    }
}

int main(){
    std::map<unsigned long long, bool> currentHarshad = {{1, false}, {2, false}, {3, false}, {4, false}, {5, false}, {6, false}, {7, false}, {8, false}, {9, false}};
    std::map<unsigned long long, bool> parentHarshad;
    unsigned long long sum = 0;
    unsigned long long count = 0;
    
    for(int i = 2; i < MAX_DIGITS; i++)
    {        
        populateHarshad(currentHarshad, parentHarshad);
        // std::cout << "i: " << i << std::endl;
        // std::cout << "Size of currentHarshad: " << currentHarshad.size() << std::endl;
        
        for(auto it = currentHarshad.begin(); it != currentHarshad.end(); it++)
        {          

            if(it->second)
            {
                unsigned long long num = it->first;

                for(int i = 0; i < 10; i++)
                {
                    unsigned long long newNum = num * 10 + i;
                    if(isPrime(newNum))
                        sum += newNum;
                        count++;                        
                }
            }
        }
    }

    std::cout << sum << std::endl;    
    return 0;
}
