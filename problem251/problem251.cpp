#include <iostream>  // For input/output functions
#include <cmath>     // For math functions like sqrt
#include <cstdio>    // For printf

// Maximum limit constant
const long long MAX_LIMIT = 110000000;

// Extended Euclidean algorithm to solve ax + by = gcd(a, b)
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long gcd = extendedGCD(b, a % b, x, y);
    long long temp = x - (a / b) * y;
    x = y;
    y = temp;
    return gcd;
}

// Function to solve the congruence equation a*x ≡ c (mod m)
long long solveCongruence(long long a, long long c, long long m, long long &x, long long &y) {
    long long gcd = extendedGCD(a, m, x, y);
    if (c % gcd != 0) return -1;  // No solution exists

    long long mCoef = c / gcd;
    long long mAbs = std::abs(a / gcd);
    y *= mCoef;
    y = (y % mAbs + mAbs) % mAbs;
    x = (c - m * y) / a;
    return std::abs(gcd);
}

int main() {
    long long gcdResult, mValue;
    
    // Upper limits for loop bounds (assumed not yet proven)
    long long maxQ = std::sqrt(((MAX_LIMIT + 1) / 3 * 8 - 3) / 5) + 3;
    long long maxP = std::sqrt((MAX_LIMIT + 1) / 5) + 3;

    long long totalSolutions = 0;

    // Iterate through possible values of q and p
    for (long long q = 1; q <= maxQ; q += 2) {
        for (long long p = 1; p <= maxP && q * q * 3 + p * p * 8 + q * 8 <= MAX_LIMIT * 8 - 1; p++) {
            if (solveCongruence(p * 8, 3, -q * q, gcdResult, mValue) != 1) continue;

            long long startValue = gcdResult * q + mValue * p * p + gcdResult * p * 3;
            long long stepValue = q * q * q + p * q * q * 3 + p * p * p * 8;

            // Count the number of valid solutions
            totalSolutions += (startValue <= MAX_LIMIT + 1 ? (MAX_LIMIT + 1 - startValue) / stepValue + 1 : 0);
        }
    }

    // Output the total number of solutions found
    std::printf("%lld\n", totalSolutions);

    return 0;
}
