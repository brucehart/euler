#include <iostream>
#include <gmp.h>
#include <set>
#include <cstring>

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

    mpz_nextprime(num, num);
    unsigned long long prime = mpz_get_ui(num);
    mpz_clear(num);
    return prime;
}

bool containsTwoHundred(mpz_t n) {
    char* str = mpz_get_str(NULL, 10, n);
    for (int i = 0; i < strlen(str) - 2; i++) {        
        if (str[i] == '2' && str[i + 1] == '0' && str[i + 2] == '0') {
            free(str);
            return true;
        }
    }
    free(str);
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
            mpz_set_str(newNum, str, 10);  // base should be 10, not 15

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
    unsigned long long p2 = 3;
    unsigned long long count = 0;

    while (true) {
        for (int i = 0; i < 1000; i++){
            createSqubes(p1, p2);
            unsigned long long next = next_prime(p1);
            p1 = p2;
            p2 = next;
        }

        while (!squbes.empty()) {
            unsigned long long sqube = *squbes.begin();
            squbes.erase(squbes.begin());
            mpz_t n;
            mpz_init(n);
            mpz_set_ui(n, sqube);
            if (containsTwoHundred(n) && primeProof(sqube)) {
                validSqubes.insert(sqube);
                count++;
            }
            mpz_clear(n);

            if (count == 200) {                
                return sqube;
            }
        }        
    }
}

int main() {
	std::cout << find200thSqube() << std::endl;
	return 0;
}
