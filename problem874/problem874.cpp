#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

// Basic primality test for small numbers
// This function checks whether a number `n` is prime
bool isPrime(int n) {
    if (n <= 1) return false;  // Numbers less than or equal to 1 are not prime
    if (n == 2 || n == 3) return true;  // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return false;  // Even numbers and multiples of 3 are not prime

    // For numbers greater than 3, check for divisibility starting from 5
    // and skip numbers that are multiples of 2 or 3 by incrementing in steps of 6
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;  // Divisible by `i` or `i+2` means not prime
    }
    return true;  // If no divisors found, `n` is prime
}

// Generate all prime numbers less than `n` using the `isPrime` function
std::vector<int> generatePrimes(int n) {
    std::vector<int> primes;
    for (int i = 2; primes.size() < n; i++) {  // Start from 2, the smallest prime
        if (isPrime(i)) {  // If `i` is prime
            primes.push_back(i);  // Insert the prime into the set
        }
    }

    return primes;
}

int main(){
    cpp_int max_sum = 0;        
    auto primeList = generatePrimes(7001);    
    std::vector<int> a(primeList[7000], 6999);
    
    std::vector<int> primeDiff(primeList.size()-1, 0);
    int minDiffIdx = 0; 
    int minDiff = 0;
    

    for(int i = 0; i < primeList.size()-1; i++)
        primeDiff[i] = primeList[i+1] - primeList[i];

    auto sum_a = std::accumulate(a.begin(), a.end(), 0);

    while(sum_a % 7000 != 0)
    {
        minDiffIdx = 0;
        minDiff = 99999999;

        for(int i = 0; i < a.size(); i++)
        {
            if (a[i] == 0)
                continue;            

            if(primeDiff[a[i] - 1] < minDiff)
            {                
                minDiff = primeDiff[a[i] - 1];
                minDiffIdx = i;
            }
        } 

        a[minDiffIdx]--;
        sum_a--;
    }

    sum_a = std::accumulate(a.begin(), a.end(), 0);
    std::cout << sum_a << std::endl;

    for(int i = 0; i < a.size(); i++)    
         max_sum += primeList[a[i]];
    

    
    std::cout << max_sum << std::endl;

    for (int i = 0; i < 20 && i < primeList.size(); ++i) {
        std::cout << primeList[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}