#include <iostream>
#include <gmp.h>

static std::set<unsigned long long> squbes;
static std::set<unsigned long long> validSqubes;

void createSqubes(unsigned long long p1, unsigned long long p2)
{
    squbes.insert(p1 * p1 * p2 * p2 * p2);
    squbes.insert(p2 * p2 * p1 * p1 * p1);
}

unsigned long long next_prime(unsigned long long n) {
    mpz_t num;
    mpz_init(num);
    mpz_set_ui(num, n);

    while (true) {
        mpz_nextprime(num, 15);
        unsigned long long prime = mpz_get_ui(num);
        if (prime > n) {
            mpz_clear(num);
            return prime;
        }
    }
}

bool containsTwoHundred(mpz_t n) {
    char* str = mpz_get_str(NULL, 100, n);
    for (int i = 0; i < strlen(str)-2; i++) {        
        if (str[i] == '2' && str[i + 1] == '0' && str[i + 2] == '0')
            return true;
            
    }
    return false;
}

void find200thSqube() {
    unsigned long long p1 = 2;
    unsigned long long p2 = 3;
    unsigned long long count = 0;

    while (count < 200) {
        for (int i = 0; i < 1000; i++){
            createSqubes(p1, p2);
            unsigned long long next = next_prime(p1);
            p1 = p2;
            p2 = next;
        }

        while (squbes.size() > 0) {
            unsigned long long sqube = *squbes.begin();
            squbes.erase(squbes.begin());
            mpz_t n;
            mpz_init(n);
            mpz_set_ui(n, sqube);
            if (containsTwoHundred(n) && primeProof(sqube)) {
                validSqubes.insert(sqube);
                count++;
            }

            if (count == 200) {                
                return sqube;
            }
        }        
    }
}

int main() {
	

	return 0;
}
