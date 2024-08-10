#include <iostream>
#include <vector>

using namespace std;

// Memoization table using unsigned long long
vector<vector<vector<unsigned long long>>> memo;

// Function to count valid numbers using unsigned long long
unsigned long long countValidNumbers(int digitsLeft, int prevDigit, int prevPrevDigit) {
    // Base case: No digits left
    if (digitsLeft == 0) {
        return 1; 
    }

    // Check if the result is already memoized
    if (memo[digitsLeft][prevDigit][prevPrevDigit] != -1) {
        return memo[digitsLeft][prevDigit][prevPrevDigit];
    }

    unsigned long long count = 0;

    // Iterate through possible current digits
    for (int currDigit = 0; currDigit <= 9; currDigit++) {
        // Check if the sum of three consecutive digits is within the limit
        if (prevDigit + prevPrevDigit + currDigit <= 9) {
            // Recursively count valid numbers for the remaining digits
            count += countValidNumbers(digitsLeft - 1, currDigit, prevDigit);
        }
    }

    // Memoize the result
    memo[digitsLeft][prevDigit][prevPrevDigit] = count;
    return count;
}

int main() {
    int totalDigits = 20; 

    // Initialize memoization table with -1 (indicating not calculated yet)
    memo.resize(totalDigits + 1, vector<vector<unsigned long long>>(10, vector<unsigned long long>(10, -1)));

    unsigned long long totalCount = 0;

    // Iterate through possible first two digits (excluding leading zero)
    for (int firstDigit = 1; firstDigit <= 9; firstDigit++) {
        for (int secondDigit = 0; secondDigit <= 9; secondDigit++) {
            // Check if the sum of the first two digits is within the limit
            if (firstDigit + secondDigit <= 9) {
                // Count valid numbers starting with these two digits
                totalCount += countValidNumbers(totalDigits - 2, secondDigit, firstDigit);
            }
        }
    }

    cout << totalCount << endl;

    return 0;
}
