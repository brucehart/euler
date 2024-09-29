#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <primesieve.hpp>

static int N = 1000000;

int main(){
    std::vector<int> primes;
    std::set<int> unused_primes;
    std::set<int> used_primes;
    std::vector<int> toCheck;
    std::vector<std::set<int>> divisorSets;
    double logResult = 0.0;

    primesieve::generate_primes(N, &primes);

    for (int i = 3; i < N; i+=10){
        if (std::binary_search(primes.begin(), primes.end(), i))
            used_primes.insert(i);       
        else
            toCheck.push_back(i);
            
    }

    for (const auto& prime : primes) {
        if (used_primes.find(prime) == used_primes.end()) {
            unused_primes.insert(prime);
        }
    }

    for(int i: toCheck)
    {
        bool prime_matched = false;             
        
        for (auto p: used_primes)
        {
            if (p > i) break;

            if (i % p == 0)
            {
                prime_matched = true;
                break;            
            }
        }

        if (prime_matched){
            toCheck.erase(std::remove(toCheck.begin(), toCheck.end(), i), toCheck.end());
            continue;
        }
    
        std::set<int> divisors;

        for (auto p: unused_primes)
        {           
            if (p > i) break;
            if (i % p == 0)
            {
                divisors.insert(p);                
            }
        }

        divisorSets.push_back(divisors);        
        toCheck.erase(std::remove(toCheck.begin(), toCheck.end(), i), toCheck.end());
    }

    std::sort(divisorSets.begin(), divisorSets.end(), [&](const std::set<int>& a, const std::set<int>& b) {
        return *(a.begin()) > *(b.begin());
    });

    while(!divisorSets.empty())
    {
        std::set<int> currentSet = divisorSets[0];
        divisorSets.erase(divisorSets.begin());
        used_primes.insert(*(currentSet.begin()));
        int primeVal = *(currentSet.begin());

        divisorSets.erase(
            std::remove_if(divisorSets.begin(), divisorSets.end(), 
                           [primeVal](const std::set<int>& s) { return s.find(primeVal) != s.end(); }), 
            divisorSets.end());       
    }
   
    for (const auto& prime : used_primes) {
        logResult += log(prime);
    }
    
    std::cout << std::fixed << std::setprecision(6) << logResult << std::endl;
    

    return 0;
}