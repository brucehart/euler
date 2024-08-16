#include <iostream>
#include <string>

// Function to check if a number is prime
bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// Function to find the smallest k such that the repunit R(k) is divisible by n
int find_least_divisible_repunit(int n) {
    if (n % 2 == 0 || n % 5 == 0)
        return 0;
    
    int repunit_mod_n = 1; // Equivalent to R(k) mod n
    int power_mod_n = 1;   // Equivalent to 10^k mod n
    int k = 1;

    // Loop until the repunit is divisible by n
    while (repunit_mod_n % n != 0) {
        k++;
        power_mod_n = (power_mod_n * 10) % n;
        repunit_mod_n = (repunit_mod_n + power_mod_n) % n;
    }
    return k;
}

int main() {
    int total_sum = 0;
    int count_found = 0;

    // Loop through odd numbers starting from 7 until 25 numbers are found
    for (int i = 7; count_found < 25; i += 2) {
        // Check conditions to include the current number
        if (i % 5 != 0 && !is_prime(i) && (i - 1) % find_least_divisible_repunit(i) == 0) {
            total_sum += i;
            count_found++;
        }
    }

    // Print the result
    std::cout << total_sum << std::endl;
    return 0;
}
