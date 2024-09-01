#include <iostream>
#include <gmp.h>
#include <set>
#include <cstring>

static std::set<unsigned long long> validSqubes;

std::pair<unsigned long long, unsigned long long> createSqubes(unsigned long long p1, unsigned long long p2)
{
    return {p1 * p1 * p2 * p2 * p2, p2 * p2 * p1 * p1 * p1};
}

unsigned long long next_prime(unsigned long long n) {
    mpz_t num;
    mpz_init(num);
    mpz_set_ui(num, n);

    mpz_nextprime(num, num);
    unsigned long long prime = mpz_get_ui(num);
    mpz_clear(num);
        
    return prime;
}

bool containsTwoHundred(unsigned long long n) {
    mpz_t num;
    mpz_init(num);
    mpz_set_ui(num, n);
    
    char* str = mpz_get_str(NULL, 10, num);
    for (int i = 0; i < strlen(str) - 2; i++) {        
        if (str[i] == '2' && str[i + 1] == '0' && str[i + 2] == '0') {
            free(str);
            mpz_clear(num);
            return true;
        }
    }
    free(str);
    mpz_clear(num);
    return false;
}

bool primeProof(unsigned long long n) {
    mpz_t num;
    mpz_init(num);
    mpz_set_ui(num, n);

    char* str = mpz_get_str(NULL, 10, num);
    bool isPrimeProof = true;

    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];
        for (int j = 0; j < 10; j++) {
            if (j == c - '0') continue;
            str[i] = j + '0';

            mpz_t newNum;
            mpz_init(newNum);
            mpz_set_str(newNum, str, 10);

            if (mpz_probab_prime_p(newNum, 15) > 0) {
                isPrimeProof = false;
                mpz_clear(newNum);
                break;
            }
            mpz_clear(newNum);
        }
        if (!isPrimeProof) break;
        str[i] = c;
    }

    free(str);
    mpz_clear(num);
    return isPrimeProof;
}

unsigned long long find200thSqube() {
    unsigned long long p1 = 2;
    std::set<unsigned long long> primes;

    while (p1 < 20000)
    {
        primes.insert(p1);
        p1 = next_prime(p1);
    }

    for (int i=0;i<primes.size();i++)
    {
        if (i % 1000 == 0) std::cout << i << " of " << primes.size() << std::endl;
        for(int j=i;j<primes.size();j++)
        {
            auto s = createSqubes(*std::next(primes.begin(), i), *std::next(primes.begin(), j));

        if (containsTwoHundred(s.first) && primeProof(s.first))
            validSqubes.insert(s.first);

        if (containsTwoHundred(s.second) && primeProof(s.second))
            validSqubes.insert(s.second);
        }
    }


    if (validSqubes.size() < 200)
        return 0;

    auto it = validSqubes.begin();
    std::advance(it, 199); // Advance to the 200th element (index 199)
    return *it;
}

int main() {
    std::cout << find200thSqube() << std::endl;
    return 0;
}
