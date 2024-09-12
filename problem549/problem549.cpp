#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
#include <set>
#include <gmp.h>
#include <iomanip>  // for std::setw
#include <map>
#include <deque>

static const unsigned int N = 100000000;  // Smaller value for testing
unsigned long long sum = 0;

std::vector<unsigned int> product(N+1,1);
std::vector<bool> summed(N+1, false);
unsigned int sum_count = 0;
std::map<unsigned int, unsigned int> prime_count;
std::map<unsigned int, bool> prime_filled;


void updateRemaining(unsigned int p, unsigned int m)
{   
    for (int i = p; i <= N; i+=p)
    {

        if (summed[i]){            
            continue;
        }

        if ((i/product[i]) % p == 0)
            product[i] *= p;
        
        if (product[i] == i)
        {
            summed[i] = true;
            sum_count++;
            sum += m;
        }
    }
}

std::vector<unsigned int> primeFactorization(int n) {
    mpz_t n_mpz;
    std::vector<unsigned int> primeFactors;
    
    mpz_init_set_ui(n_mpz, n);
    if (mpz_probab_prime_p(n_mpz, 15) > 0) {
        primeFactors.push_back(n);
    }
    mpz_clear(n_mpz);

    if (primeFactors.size() > 0)
        return primeFactors;

    while (n % 2 == 0) {
        primeFactors.push_back(2);
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            primeFactors.push_back(i);
            n /= i;
        }
    }

    if (n > 2) {
        primeFactors.push_back(n);
    }

    return primeFactors;
}

int main() {
    unsigned int nextPrime = 1;  
    summed[0] = true;
    summed[1] = true;     

    for (unsigned int m = 2; m < N; m++)
    {
        
        if (m % 10000 == 0) std::cout << "m: " << m << " | Sum Count: " << sum_count << std::endl;

        auto primes = primeFactorization(m);

        for (auto p: primes)
        {
            if (prime_filled[p]) continue;
            
            prime_count[p]++;
            
            if (pow(p, prime_count[p]) >= N)  
            {
                //std::cout << "pow(" << p << "," << prime_count[p] << ")=" << pow(p, prime_count[p]) << std::endl;         
                prime_filled[p] = true;            
            }
            else
            {
                updateRemaining(p, m);
            }
        }
    }

    int falseCount = 0;
    for (int i = 0; i < N && falseCount < 20; ++i) {
        if (!summed[i]) {
            std::cout << "Index " << i << " is false. | " << product[i] << std::endl;
            ++falseCount;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
