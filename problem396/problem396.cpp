#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to convert a number to its representation in a given base
vector<int> convertToBase(int number, int base) {
    vector<int> digits;
    while (number > 0) {
        digits.push_back(number % base);
        number /= base;
    }
    return digits;
}

// Function to interpret a number represented in base "base" in a different base "base + 1"
long long interpretInBase(const vector<int>& digits, int base) {
    long long value = 0;
    for (int i = digits.size() - 1; i >= 0; --i) {
        value = value * base + digits[i];
    }
    return value;
}

// Function to compute G(n) for the weak Goodstein sequence
long long computeG(int n) {
    long long g = n;
    int base = 2;
    long long steps = 0;

    while (g > 0) {
        steps++;
        // Convert g to base 'base' representation
        vector<int> digits = convertToBase(g, base);
        // Interpret digits as a number in base 'base + 1'
        g = interpretInBase(digits, base + 1) - 1;
        base++;
    }
    return steps;
}

// Function to generate the weak Goodstein sequence for a given number n
long long goodstein_sequence_length(int n) {
    long long g = n;
    long long length = 1; // Include the initial element
    int base = 2;

    while (g != 0) {
        // Convert g to base (base) representation and interpret it as base+1
        vector<int> digits;
        long long temp = g;
        while (temp > 0) {
            digits.push_back(temp % base);
            temp /= base;
        }

        // Calculate g_{k+1} in base (base + 1)
        g = 0;
        long long multiplier = 1;
        for (int digit : digits) {
            g += digit * multiplier;
            multiplier *= (base + 1);
        }

        // Subtract 1
        g -= 1;

        // Increase the base
        base++;
        length++;

        if (length % 10000 == 0) {
            std::cout << "-----" << length << std::endl;
        }
    }

    return length-1;
}

int main() {
    const int MAX_N = 7;
    const long long MOD = 1000000000; // To find the last 9 digits
    long long sum = 0;    

    long long total = 0;
    for (int n = 1; n < 16; ++n) {
        long long G_n = computeG(n);
        std::cout << "###" << n << ":" << G_n << std::endl;
        total += G_n;
    }

    std::cout << "Total: " << total << std::endl;

    for (int n = 1; n <= MAX_N; ++n) {
        
        long long length = goodstein_sequence_length(n);
        std::cout << "***" << n << ":" << length << std::endl;
        sum = (sum + length) % MOD;
    }

    cout << "The last 9 digits of the sum of G(n) for 1 <= n < 16 are: " << sum << endl;
    return 0;
}
