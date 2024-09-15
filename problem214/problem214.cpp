#include <iostream>
#include <map>
#include <gmp.h>

std::map<int, int> chainLengths;
std::map<int, int> phiValues;

// Function to calculate the Euler's Totient function φ(n)
int phi(int n) {
    if (phiValues.find(n) != phiValues.end())
        return phiValues[n];

    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return phiValues[n] = result;
}

bool isPrime(unsigned long long num)
{
    mpz_t n;
    mpz_init(n);
    mpz_set_ui(n, num);

    int result = mpz_probab_prime_p(n, 15); // 15 is the number of Miller-Rabin iterations

    if (result > 0) {
        return true; // num is probably prime
    } else {
        return false; // num is definitely composite
    }

    mpz_clear(n);
}

int chainLength(int n, int depth = 0) {
    int cL;

    if (depth > 25)
        return 26;

    if (n == 1)
        return 1;

    if (chainLengths.find(n) != chainLengths.end())
        return chainLengths[n];
           
    cL = 1 + chainLength(phi(n), depth+1);
    
    if (cL > 25)
        cL = 26;

    return chainLengths[n] = cL;
}

int main(){
    static const int limit = 40000000;
    unsigned long long sum = 0;

    int n = 9500000;

    while(n < limit){        

        if (!isPrime(n))
        {
            n++;
            continue;
        }        
        if (chainLength(n) == 25)
            sum += n;
        n++;
    }

    std::cout << sum << std::endl;

    return 0;
}