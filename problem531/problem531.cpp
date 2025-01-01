#include <iostream>
#include <vector>
#include <algorithm> // Removed usage of std::gcd if C++17 is not available
#include <cstdint>   // for fixed-width integer types

//------------------------------------------------------------------------------
 // Compute Euler's totient function for all integers [0..maxN] using a sieve
 // Similar to a sieve of Eratosthenes but adapted for phi.
 //------------------------------------------------------------------------------
static std::vector<int> computePhiUpTo(int maxN)
{
    std::vector<int> phi(maxN + 1);
    // Initialize phi[i] = i
    for (int i = 0; i <= maxN; ++i) {
        phi[i] = i;
    }

    // Sieve update: if i is prime, then for each multiple k*i,
    // phi(k*i) = phi(k*i) / i * (i - 1)
    for (int i = 2; i <= maxN; ++i) {
        if (phi[i] == i) { 
            // i is prime
            for (int k = i; k <= maxN; k += i) {
                phi[k] -= phi[k] / i;
            }
        }
    }
    return phi;
}

//------------------------------------------------------------------------------
 // Custom GCD function using Euclidean algorithm
 //------------------------------------------------------------------------------
static std::int64_t customGCD(std::int64_t a, std::int64_t b)
{
    while (b != 0) {
        std::int64_t temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

//------------------------------------------------------------------------------
 // Extended Euclidean Algorithm:
 // Returns (g, x, y) such that a*x + b*y = g = gcd(a, b).
 //------------------------------------------------------------------------------
static void extendedEuclid(std::int64_t a, std::int64_t b,
                           std::int64_t& x, std::int64_t& y,
                           std::int64_t& g)
{
    // Base case
    if (b == 0) {
        g = a;
        x = 1;
        y = 0;
        return;
    }

    // Recursively apply EEA
    std::int64_t x1 = 0, y1 = 0;
    extendedEuclid(b, a % b, x1, y1, g);
    // Update x, y using results of recursion
    x = y1;
    y = x1 - (a / b) * y1;
}

//------------------------------------------------------------------------------
 // Solve the system of congruences via the CRT:
 //   x ≡ a (mod n)
 //   x ≡ b (mod m)
 //
 // Returns the smallest non-negative solution if it exists, or 0 if no solution.
 //------------------------------------------------------------------------------
static std::int64_t solveCRT(std::int64_t a, std::int64_t n,
                             std::int64_t b, std::int64_t m)
{
    // 1) Check feasibility: gcd(n, m) must divide (b - a)
    std::int64_t g = customGCD(n, m);
    if ((b - a) % g != 0) {
        return 0; // No solution exists
    }

    // 2) Solve n*k ≡ (b - a) (mod m).  Let (b-a) = d*g, where d = (b-a)/g.
    //    Let n = g*n', m = g*m'. We want: n' * k ≡ d (mod m').
    //    Use the extended Euclidean algorithm to invert n' modulo m'.

    std::int64_t nPrime = n / g;
    std::int64_t mPrime = m / g;
    std::int64_t d = (b - a) / g;

    // Extended Euclid to find x,y such that nPrime*x + mPrime*y = 1
    std::int64_t xEea, yEea, gEea;
    extendedEuclid(nPrime, mPrime, xEea, yEea, gEea);
    // gEea should be 1, since nPrime and mPrime are coprime.

    // 3) The particular solution for k modulo mPrime is:  k0 = d * xEea  (mod mPrime)
    //    Then x = a + n*k0. We reduce x modulo the lcm(n,m) to get the smallest.
    //    lcm(n,m) = (n*m)/g.
    std::int64_t k0 = (d * xEea) % mPrime;
    if (k0 < 0) {
        k0 += mPrime; // ensure non-negative
    }

    // This is one valid k. Then x = a + n*k.
    __int128 x0 = ( (__int128)a + (__int128)n * k0 );

    // 4) Ensure smallest non-negative solution by taking x0 mod lcm(n,m).
    std::int64_t lcmVal = (n / g) * m; // or (n*m)/g
    std::int64_t result = static_cast<std::int64_t>(x0 % lcmVal);
    if (result < 0) {
        result += lcmVal;
    }

    return result;
}

//------------------------------------------------------------------------------
 // f(n, m) = g(phi(n), n, phi(m), m) where g(...) solves the CRT system above.
 //------------------------------------------------------------------------------
int main()
{
    const int START = 1000000;
    const int END   = 1005000; // range is [START .. END)
    // Precompute phi(k) for k up to END-1
    std::vector<int> phi = computePhiUpTo(END - 1);

    // We'll use a 128-bit accumulator to avoid overflow (in case it gets large).
    __int128 totalSum = 0;

    // Main double loop
    for (int n = START; n < END; ++n) {
        for (int m = n + 1; m < END; ++m) {
            std::int64_t a = phi[n];
            std::int64_t b = phi[m];
            // Solve x ≡ a (mod n), x ≡ b (mod m)
            std::int64_t val = solveCRT(a, n, b, m);
            totalSum += val;
        }
    }

    // Output the result as a 64-bit value if it fits, or handle __int128 appropriately.
    // Here, we assume it fits in 64 bits. If not, additional handling is required.
    // For demonstration, we'll cast and output the lower 64 bits.
    std::uint64_t finalAnswer = static_cast<std::uint64_t>(totalSum);

    std::cout << finalAnswer << std::endl;
    return 0;
}
