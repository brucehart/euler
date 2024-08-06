#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <string>

#define PI_A "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
#define PI_B "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"

#define MAX_N 17

uint64_t calculateTermIndex(int n) {
    uint64_t termIndex = 127 + 19 * n;
    for (int i = 0; i < n; ++i) {
        termIndex *= 7;
    }
    return termIndex;
}

char findNthDigit(uint64_t n, const std::vector<uint64_t>& sequenceLengths, const std::string& A, const std::string& B, int64_t seqIndex = -1) {
    if (seqIndex == 0 && n <= A.size()) {
        return A[n - 1];
    }
    if (seqIndex == 1 && n <= B.size()) {
        return B[n - 1];
    }

    if (seqIndex == -1) {
        seqIndex = 0;
        while (sequenceLengths[seqIndex] < n) {
            seqIndex++;
        }
    }

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
    for (int i = 0; i <= MAX_N; ++i) {
        termIndices.push_back(calculateTermIndex(i));
    }

    std::vector<uint64_t> sequenceLengths = { A.size(), B.size() };
    while (sequenceLengths.back() < termIndices.back()) {
        sequenceLengths.push_back(sequenceLengths[sequenceLengths.size() - 2] + sequenceLengths.back());
    }

    uint64_t resultSum = 0;
    for (int i = 0; i <= MAX_N; ++i) {
        uint64_t multiplier = std::pow(10, i);
        uint64_t termIndex = termIndices[i];
        char digit = findNthDigit(termIndex, sequenceLengths, A, B);
        resultSum += multiplier * (digit - '0');
    }

    std::cout << resultSum << std::endl;

    return 0;
}
