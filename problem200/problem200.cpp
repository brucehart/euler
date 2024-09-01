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
    while (n >= 100) {
        if (n % 1000 == 200) {  // Check the last three digits
            return true;
        }
        n /= 10;  // Move to the next digit
    }
    return false;
}

bool primeProof(unsigned long long n) {
    unsigned long long original = n;
    unsigned long long temp;
    unsigned long long power_of_ten = 1;
    
    // Iterate over each digit in the number
    while (n / power_of_ten > 0) {
        unsigned long long current_digit = (n / power_of_ten) % 10;
        
        // Try replacing the current digit with each digit from 0 to 9 (except itself)
        for (unsigned long long i = 0; i < 10; i++) {
            if (i == current_digit) continue;

            // Create a new number with the digit replaced
            temp = original - current_digit * power_of_ten + i * power_of_ten;

            // Check if the new number is prime
            mpz_t newNum;
            mpz_init(newNum);
            mpz_set_ui(newNum, temp);
            if (mpz_probab_prime_p(newNum, 15) > 0) {
                mpz_clear(newNum);
                return false;  // Not prime-proof if any variant is prime
            }
            mpz_clear(newNum);
        }
        power_of_ten *= 10;
    }
    return true;
}

unsigned long long find200thSqube() {
    std::set<unsigned long long> primes;
    unsigned long long p1 = 2;
    unsigned long long ten_12 = 1000000000000;

    
    while(p1 < 200000)
    {
        primes.insert(p1);
        p1 = next_prime(p1);
    }

           
    for (int i=0;i<primes.size();i++)
    {       
        for (int j=i;j<primes.size();j++)
        {
            auto s = createSqubes(*std::next(primes.begin(), i), *std::next(primes.begin(), j));
            
            if (containsTwoHundred(s.first) && primeProof(s.first))
                validSqubes.insert(s.first);

            if (containsTwoHundred(s.second) && primeProof(s.second))
                validSqubes.insert(s.second);

            if (s.first > ten_12 && s.second > ten_12)
                break;
        }
    }        

    if (validSqubes.size() < 200) {
        std::cout << "Not enough squbes found: " << validSqubes.size() << std::endl;
        return 0;
    }


    auto it = validSqubes.begin();
    std::advance(it, 199); // Advance to the 200th element (index 199)
    return *it;
}

int main() {
    std::cout << find200thSqube() << std::endl;
    return 0;
}
