#include <iostream>

// Function to reverse a number
int reverseNumber(int n) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + (n % 10);
        n /= 10;
    }
    return rev;
}

// Function to check if all digits of a number are odd
bool allOddDigits(int n) {
    while (n > 0) {
        if ((n % 10) % 2 == 0) {
            return false;
        }
        n /= 10;
    }
    return true;
}

// Function to get the first digit of a number
int firstDigit(int n) {
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

// Function to get the last digit of a number
int lastDigit(int n) {
    return n % 10;
}

int main() {
    int count = 0;
    for (int n = 1; n < 1000000000; ++n) {
        if (n % 10 == 0) continue; // Skip numbers ending with 0 to avoid leading zeroes in reverse

        int first = firstDigit(n);
        int last = lastDigit(n);

        // Skip numbers where the first and last digits are both even or both odd
        if ((first % 2 == last % 2)) continue;

        int rev = reverseNumber(n);
        int sum = n + rev;

        if (allOddDigits(sum)) {
            ++count;
        }
    }
    std::cout << count << std::endl;
    return 0;
}
