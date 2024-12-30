#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>

// A structure just to hold factorials and inverse factorials mod p
struct Factorials {
    std::vector<uint64_t> fact;  // fact[i] = i! mod p
    std::vector<uint64_t> invf;  // invf[i] = (i!)^{-1} mod p
};

// Extended Euclid to find x, y s.t. a*x + b*y = gcd(a,b).
// Returns gcd(a,b).  Typically used to find modular inverse.
static int64_t extendedGCD(int64_t a, int64_t b, int64_t &x, int64_t &y)
{
    if (b == 0) {
        x = 1; 
        y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t g = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Compute modular inverse of a mod m (assuming m is prime or at least that gcd(a,m)=1).
static uint64_t modInverse(uint64_t a, uint64_t m)
{
    // Using Extended Euclid
    int64_t x, y;
    int64_t g = extendedGCD((int64_t)a, (int64_t)m, x, y);
    // For safety, though here g should be 1 if a and m are coprime
    if (g != 1) {
        // No inverse exists
        return 0;
    }
    // x might be negative; normalize it
    int64_t res = x % (int64_t)m;
    if (res < 0) {
        res += m;
    }
    return (uint64_t)res;
}

// Precompute factorials and inverse factorials mod p
static Factorials buildFactorials(int p)
{
    Factorials f;
    f.fact.resize(p);
    f.invf.resize(p);
    f.fact[0] = 1;
    for (int i = 1; i < p; i++) {
        f.fact[i] = (uint64_t)f.fact[i-1] * (uint64_t)i % p;
    }
    // invf[p-1] = (p-1)!^{-1} mod p
    f.invf[p-1] = modInverse(f.fact[p-1], p);
    // inverse factorial downward
    for (int i = p-2; i >= 0; i--) {
        f.invf[i] = (uint64_t)f.invf[i+1] * (uint64_t)(i+1) % p;
    }
    return f;
}

// Compute nCk mod p when 0 <= k <= n < p (i.e., "small" binomial mod p).
// We assume factorials.fact[i] = i! mod p and factorials.invf[i] = (i!)^{-1} mod p
static uint64_t binomSmall(int n, int k, int p, const Factorials &factorials)
{
    if (k < 0 || k > n) {
        return 0;
    }
    return (uint64_t)factorials.fact[n] 
         * (uint64_t)factorials.invf[k] % p 
         * (uint64_t)factorials.invf[n-k] % p;
}

// Compute C(n, k) mod p using Lucas's Theorem and precomputed factorials
// for all 0 <= x < p.
static uint64_t binomLarge(uint64_t n, uint64_t k, int p, const Factorials &factorials)
{
    // Lucas's theorem states:
    // C(n, k) mod p =>  C(n_i, k_i) mod p,  where n_i, k_i are base-p digits
    // of n and k respectively.
    // We compute digits from least significant to most.
    uint64_t result = 1;
    while (n > 0 || k > 0) {
        int n_i = (int)(n % p);
        int k_i = (int)(k % p);
        result = (result * binomSmall(n_i, k_i, p, factorials)) % p;
        n /= p;
        k /= p;
        if (result == 0) {
            break;
        }
    }
    return result;
}

// Compute x mod (m*n) if we want x such that
// x => a (mod m)
// x => b (mod n)
// We assume gcd(m, n) = 1, and use standard CRT 2-moduli approach.
static uint64_t crt2(uint64_t a, uint64_t m,
                     uint64_t b, uint64_t n)
{
    // Solve x = a + (b - a)*inv(m, n)*m  (mod m*n).
    // We'll do everything in 128-bit to avoid overflow.
    __int128 M = (__int128)m * n;

    // Reduce a, b modulo n to get the correct difference (b - a) mod n:
    uint64_t a_mod = a % n;
    uint64_t b_mod = b % n;

    // Compute the difference mod n
    uint64_t diff = (b_mod >= a_mod) 
                    ? (b_mod - a_mod) 
                    : (b_mod + n - a_mod);

    // Compute inverse of (m mod n) modulo n
    uint64_t mInv = modInverse(m % n, n);

    // Multiply diff * mInv (mod n)
    __int128 tmp = ((__int128)diff * mInv) % n;

    // Multiply by m, then add a
    tmp = tmp * m;
    __int128 x = (__int128)a + tmp;

    // Reduce modulo m*n
    x = x % M;
    if (x < 0) {
        x += M;
    }

    return (uint64_t)x;  // safe if m*n < 2^64
}


// CRT for three pairwise-coprime moduli p, q, r
// Returns x in [0, p*q*r) such that:
//   x => x1 (mod p)
//   x => x2 (mod q)
//   x => x3 (mod r)
static uint64_t crt3(uint64_t x1, uint64_t p,
                     uint64_t x2, uint64_t q,
                     uint64_t x3, uint64_t r)
{
    // Combine x1 mod p and x2 mod q
    uint64_t x12 = crt2(x1, p, x2, q);
    // Now combine x12 mod (p*q) and x3 mod r
    return crt2(x12, p*q, x3, r);
}

// Simple sieve of Eratosthenes to get all primes up to maxN
static std::vector<int> sievePrimes(int maxN)
{
    std::vector<bool> isprime(maxN+1, true);
    isprime[0] = false; 
    isprime[1] = false;
    for (int i = 2; i * i <= maxN; i++) {
        if (isprime[i]) {
            for (int j = i*i; j <= maxN; j += i) {
                isprime[j] = false;
            }
        }
    }
    std::vector<int> result;
    for (int i = 2; i <= maxN; i++) {
        if (isprime[i]) {
            result.push_back(i);
        }
    }
    return result;
}

std::string int128ToDecimal(__int128 val) {
    bool neg = (val < 0);
    if (neg) {
        val = -val; // Make it positive
    }
    std::string result;
    while (val > 0) {
        int digit = (int)(val % 10);
        result.push_back(char('0' + digit));
        val /= 10;
    }
    if (result.empty()) {
        result = "0";
    }
    if (neg) {
        result.push_back('-');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main()
{
    // We want primes p, q, r with 1000 < p < q < r < 5000.
    // 1) Generate all primes up to 5000.
    std::vector<int> primes = sievePrimes(5000);

    // Filter only those > 1000
    std::vector<int> validPrimes;
    for (int pr : primes) {
        if (pr > 1000 && pr < 5000) {
            validPrimes.push_back(pr);
        }
    }

    // 2) Precompute C(10^18, 10^9) mod p for each prime p in validPrimes
    //    using Lucas's theorem and precomputed factorials mod p.
    const uint64_t N = 1000000000000000000ULL; // 10^18
    const uint64_t K = 1000000000ULL;         // 10^9

    // We'll store f[p] = binomial(10^18, 10^9) mod p, 
    // but we need an index-based map, not a direct array up to 5000, 
    // because we only do it for these primes.
    // For convenience, let's store in a std::vector<uint64_t> fvals
    // in the same order as validPrimes.
    std::vector<uint64_t> fvals(validPrimes.size());

    for (size_t i = 0; i < validPrimes.size(); i++) {
        int p = validPrimes[i];
        // Build factorials for p
        Factorials fac = buildFactorials(p);
        // Compute C(N, K) mod p
        fvals[i] = binomLarge(N, K, p, fac);
    }

    // 3) Sum up M(10^18,10^9, p*q*r) over all p < q < r from validPrimes
    //    using CRT( fvals[i], fvals[j], fvals[k] ) mod (p*q*r).
    // Because the sum could be very large, we'll accumulate into a 128-bit variable
    // and reduce at the end if needed.  In this problem statement, it does not say
    // to reduce the final sum by anything, so we will just output it.  We must
    // ensure we do not overflow 128 bits.  The final result can fit in 64 bits,
    // but we will be careful.

    __int128 totalSum = 0;  // 128-bit accumulator

    // Triple nested loop
    // WARNING: This could be on the order of tens of millions of iterations!
    // Make sure you have sufficient optimizations or a strategy to handle this.
    for (size_t i = 0; i + 2 < validPrimes.size(); i++) {
        for (size_t j = i + 1; j + 1 < validPrimes.size(); j++) {
            for (size_t k = j + 1; k < validPrimes.size(); k++) {
                uint64_t p = (uint64_t)validPrimes[i];
                uint64_t q = (uint64_t)validPrimes[j];
                uint64_t r = (uint64_t)validPrimes[k];

                // fvals[i] = C(N,K) mod p
                // fvals[j] = C(N,K) mod q
                // fvals[k] = C(N,K) mod r

                uint64_t valueModPQR = crt3(fvals[i], p,
                                            fvals[j], q,
                                            fvals[k], r);
                
                // Add to totalSum (128-bit) to avoid overflow
                totalSum += valueModPQR;
            }
        }
    }

    std::string finalResultStr = int128ToDecimal(totalSum);
    std::cout << finalResultStr << std::endl;
    return 0;
}

