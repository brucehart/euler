#include <iostream>
#include <string>
#include <bitset>

// Predefined pairs of squares to check for the problem
int SQUARES[9][2] = {{0, 1}, {0, 4}, {0, 9}, {1, 6}, {2, 5}, {3, 6}, {4, 9}, {6, 4}, {8, 1}};

// Function to test if the i-th bit in x is set (1)
bool testBit(int x, int i) {
    return (x & (1 << i)) != 0;
}

// Function to check if the arrangement of two dice is valid
bool isArrangementValid(int a, int b) {
    // If either die shows 6 or 9, we treat them as interchangeable
    if (testBit(a, 6) || testBit(a, 9))
        a |= (1 << 6) | (1 << 9);
    if (testBit(b, 6) || testBit(b, 9))
        b |= (1 << 6) | (1 << 9);

    // Check each pair in SQUARES to see if it's possible with the two dice
    for (const auto &sqr : SQUARES) {
        if (!(testBit(a, sqr[0]) && testBit(b, sqr[1]) || testBit(a, sqr[1]) && testBit(b, sqr[0])))
            return false;
    }
    return true;
}

// Function to count the number of set bits (1s) in an integer
int popcount(int x) {
    #if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
        // Use built-in function if available
        return __builtin_popcount(x);
    #else
        // Custom implementation if built-in function is not available
        int count = 0;
        while (x) {
            count += x & 1;
            x >>= 1;
        }
        return count;
    #endif
}

// Function to calculate the number of valid dice arrangements
std::string run() {
    int count = 0;
    // Iterate through all possible dice combinations
    for (int i = 0; i < (1 << 10); i++) {
        for (int j = i; j < (1 << 10); j++) {  // Ensure i <= j to force the dice to be orderless
            if (popcount(i) == 6 && popcount(j) == 6 && isArrangementValid(i, j))
                count++;
        }
    }
    return std::to_string(count);
}

// Main function to execute the program
int main() {
    std::cout << run() << std::endl;
    return 0;
}
