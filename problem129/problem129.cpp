#include <iostream>
#include <gmpxx.h>

// Function to calculate the greatest common divisor (GCD) of two numbers using GMP
mpz_class gcd(mpz_class a, mpz_class b) {
    while (b != 0) {
        mpz_class temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    // Initialize the limit (you can replace this with the desired value)
    mpz_class limit = 1000000; // You can increase this limit as needed

    // Start with n equal to the limit
    mpz_class n = limit;

    // Flag to determine if the required value has been found
    bool valuenotfound = true;

    // Variable to store the result
    mpz_class value = 0;

    // Continue looping until the required value is found
    while (valuenotfound) {
        // Check if gcd(n, 10) is 1
        if (gcd(n, 10) == 1) {
            // Initialize a counter to find the smallest 'counter' such that 10^counter % (9 * n) == 1
            mpz_class counter = 1;
            while (true) {
                // Check if 10^counter % (9 * n) == 1
                mpz_class mod_result;
                mpz_class nine_times_n = 9 * n; // Explicit conversion

                mpz_powm_ui(mod_result.get_mpz_t(), mpz_class(10).get_mpz_t(), counter.get_ui(), nine_times_n.get_mpz_t()); 

                if (mod_result == 1) {
                    break;
                }

                // Increment the counter
                counter++;

                // If counter exceeds the limit, set the value and exit the loop
                if (counter > limit) {
                    value = n;
                    valuenotfound = false;
                    break;
                }
            }
        }

        // Increment n for the next iteration
        n++;
    }

    // Output the found value
    std::cout << value << std::endl;

    return 0;
}