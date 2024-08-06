//problem230.cpp
// Author: Bruce Hart <bruce.hart@gmail.com>

// For any two strings of digits, A and B, we define F_A,B to be the sequence (A,B,AB,BAB,ABBAB,...) in which each term is the concatenation of the previous two.

// Further, we define D_A,B(n) to be the nth digit in the first term of F_A,B that contains at least n digits.

// Example:

// Let A=1415926535, B=8979323846. We wish to find D_A,B(35), say.

// The first few terms of FA,B are:
// 1415926535
// 8979323846
// 14159265358979323846
// 897932384614159265358979323846
// 14159265358979323846897932384614159265358979323846

// Then D_A,B(35) is the 35th digit in the fifth term, which is 9.

// Now we use for A the first 100 digits of π behind the decimal point:

// 14159265358979323846264338327950288419716939937510 
// 58209749445923078164062862089986280348253421170679

// and for B the next hundred digits:

// 82148086513282306647093844609550582231725359408128 
// 48111745028410270193852110555964462294895493038196 .

// Find ∑n = 0,1,...,17   10^n * D_A,B((127+19n)×7^n) .

#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <string>

// Define the first 100 digits of π behind the decimal point
#define PI_A "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
// Define the next 100 digits of π behind the decimal point
#define PI_B "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"

#define MAX_N 17

/**
 * @brief Calculate the nth term index as defined by the problem
 * 
 * @param n The term number
 * @return uint64_t The computed term index
 */
uint64_t calculateTermIndex(int n) {
    uint64_t termIndex = 127 + 19 * n;
    for (int i = 0; i < n; ++i) {
        termIndex *= 7;
    }
    return termIndex;
}

/**
 * @brief Recursively find the nth digit in the sequence F_A,B
 * 
 * @param n The position of the digit to find
 * @param sequenceLengths Vector of lengths of the sequence terms
 * @param A The string A (first 100 digits of π)
 * @param B The string B (next 100 digits of π)
 * @param seqIndex The current sequence index being considered
 * @return char The nth digit in the sequence
 */
char findNthDigit(uint64_t n, const std::vector<uint64_t>& sequenceLengths, const std::string& A, const std::string& B, int64_t seqIndex = -1) {
    // Check if we are looking in A or B
    if (seqIndex == 0 && n <= A.size()) {
        return A[n - 1];
    }
    if (seqIndex == 1 && n <= B.size()) {
        return B[n - 1];
    }

    // If seqIndex is not set, find the correct sequence index
    if (seqIndex == -1) {
        seqIndex = 0;
        while (sequenceLengths[seqIndex] < n) {
            seqIndex++;
        }
    }

    // Recursively determine the source of the nth digit
    if (n > sequenceLengths[seqIndex - 2]) {
        return findNthDigit(n - sequenceLengths[seqIndex - 2], sequenceLengths, A, B, seqIndex - 1);
    } else {
        return findNthDigit(n, sequenceLengths, A, B, seqIndex - 2);
    }
}

int main() {
    std::string A = PI_A;
    std::string B = PI_B;

    std::vector<uint64_t> termIndices;
    // Create a vector of term indices that we will be looking for
    for (int i = 0; i <= MAX_N; ++i) {
        termIndices.push_back(calculateTermIndex(i));
    }

    std::vector<uint64_t> sequenceLengths = { A.size(), B.size() };
    // Generate the sequence lengths until the last required term index
    while (sequenceLengths.back() < termIndices.back()) {
        sequenceLengths.push_back(sequenceLengths[sequenceLengths.size() - 2] + sequenceLengths.back());
    }

    uint64_t resultSum = 0;
    // Calculate the required sum of digits as per the problem statement
    for (int i = 0; i <= MAX_N; ++i) {
        uint64_t multiplier = std::pow(10, i);
        uint64_t termIndex = termIndices[i];
        char digit = findNthDigit(termIndex, sequenceLengths, A, B);
        resultSum += multiplier * (digit - '0');
    }

    std::cout << resultSum << std::endl;

    return 0;
}
