#include <iostream>
#include <sstream>

unsigned long long power(int base, int exp) {
    unsigned long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

unsigned long long solve() {
    unsigned long long total = 0;
    int base = 16;

    for (int length = 1; length <= 16; length++) {
        // Total number of numbers of length `length` without leading zeros
        unsigned long long allNumbers = 15 * power(base, length - 1);

        // Directly calculate the number of valid numbers
        unsigned long long validNumbers = allNumbers - 43 * power(15, length - 1) + 41 * power(14, length - 1) - power(13, length);

        total += validNumbers;
    }

    return total;
}

int main() {
    unsigned long long result = solve();

    // Output the result in hexadecimal (upper case)
    std::cout << std::hex << std::uppercase << result << std::endl;
   
    return 0;
}
