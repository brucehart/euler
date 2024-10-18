#include <iostream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

// Function for floor division
cpp_int floor_div(cpp_int x, cpp_int y) {
    return x / y;
}

// Function to calculate a complex sum based on the given formula
cpp_int S(cpp_int a, cpp_int b, cpp_int c, cpp_int MOD) {
    // Calculate k as the floor of b divided by a
    cpp_int k = floor_div(b, a);

    // Reduce a, b, and c modulo MOD to simplify calculations
    a %= MOD;
    b %= MOD;
    c %= MOD;

    // Calculate the total sum with different components of the formula
    cpp_int total = ((b + 1) * b / 2) % MOD; // Sum of all n (sum of first b natural numbers)

    // Add the main sum part of the formula
    total = (total + ((((k - 1) * k / 2) % MOD * (4 * a * a % MOD - 3 * a * c) % MOD) % MOD + (4 * a % MOD * k % MOD * (a - c) % MOD) % MOD) % MOD) % MOD;

    // Add the remaining terms part of the formula
    total = (total + ((b - k * a + 1) % MOD * (4 * (k + 1) % MOD * a % MOD - (3 * k + 4) % MOD * c % MOD) % MOD) % MOD) % MOD;

    return total % MOD;
}

int main() {
    cpp_int MOD = 1000000000;

    // Calculate a = 21^7
    cpp_int a = 1;
    for (int i = 0; i < 7; i++) {
        a *= 21;
    }

    // Calculate b = 7^21
    cpp_int b = 1;
    for (int i = 0; i < 21; i++) {
        b *= 7;
    }

    // Calculate c = 12^7
    cpp_int c = 1;
    for (int i = 0; i < 7; i++) {
        c *= 12;
    }

    // Output the result of the function S
    std::cout << S(a, b, c, MOD) << std::endl;
    return 0;
}
