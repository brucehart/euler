#include <iostream>
#include <gmp.h>
#include <set>
#include <cstring>

// Global set to store valid squbes
static std::set<unsigned long long> validSqubes;

// Function to create squbes from two prime numbers p1 and p2
std::pair<unsigned long long, unsigned long long> createSqubes(unsigned long long p1, unsigned long long p2) {
    return {p1 * p1 * p2 * p2 * p2, p2 * p2 * p1 * p1 * p1};
}

// Function to find the next prime number greater than n using GMP library
unsigned long long next_prime(unsigned long long n) {
    mpz_t num;
    mpz_init(num);               // Initialize GMP integer
    mpz_set_ui(num, n);          // Set GMP integer to n

    mpz_nextprime(num, num);     // Find the next prime greater than n
    unsigned long long prime = mpz_get_ui(num);  // Convert GMP integer to unsigned long long
    mpz_clear(num);              // Clear GMP integer to free memory
    return prime;
}

// Function to check if the number contains the digits "200" in sequence
bool containsTwoHundred(unsigned long long n) {
    while (n >= 100) {
        if (n % 1000 == 200) {  // Check the last three digits of the number
            return true;
        }
        n /= 10;  // Move to the next digit by removing the last digit
    }
    return false;
}

// Function to check if a number is prime-proof (i.e., no digit can be changed to make it prime)
bool primeProof(unsigned long long n) {
    unsigned long long original = n;  // Store the original number
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
            if (mpz_probab_prime_p(newNum, 15) > 0) {  // If the new number is prime
                mpz_clear(newNum);  // Clear GMP integer to free memory
                return false;  // Not prime-proof if any variant is prime
            }
            mpz_clear(newNum);  // Clear GMP integer to free memory
        }
        power_of_ten *= 10;  // Move to the next digit position
    }
    return true;
}

// Function to find the 200th valid sqube that contains "200" and is prime-proof
unsigned long long find200thSqube() {
    std::set<unsigned long long> primes;  // Set to store prime numbers
    unsigned long long p1 = 2;            // Start with the first prime number
    unsigned long long ten_12 = 1000000000000;  // Threshold value for sqube comparison

    // Generate a set of prime numbers less than 200,000
    while (p1 < 200000) {
        primes.insert(p1);
        p1 = next_prime(p1);
    }

    // Iterate over pairs of primes to create and check squbes
    for (int i = 0; i < primes.size(); i++) {       
        for (int j = i; j < primes.size(); j++) {
            auto s = createSqubes(*std::next(primes.begin(), i), *std::next(primes.begin(), j));
            
            // Check if the first sqube contains "200" and is prime-proof
            if (containsTwoHundred(s.first) && primeProof(s.first))
                validSqubes.insert(s.first);

            // Check if the second sqube contains "200" and is prime-proof
            if (containsTwoHundred(s.second) && primeProof(s.second))
                validSqubes.insert(s.second);

            // Stop the inner loop if both squbes are greater than the threshold
            if (s.first > ten_12 && s.second > ten_12)
                break;
        }
    }        

    // If fewer than 200 valid squbes are found, print a message and return 0
    if (validSqubes.size() < 200) {
        std::cout << "Not enough squbes found: " << validSqubes.size() << std::endl;
        return 0;
    }

    // Find and return the 200th valid sqube
    auto it = validSqubes.begin();
    std::advance(it, 199); // Advance to the 200th element (index 199)
    return *it;
}

// Main function to execute the program
int main() {
    std::cout << find200thSqube() << std::endl;  // Print the 200th sqube
    return 0;
}
