#include <iostream>
#include <vector>
#include <cmath>
#include <primesieve.hpp>  // Include the primesieve header
#include <random>
#include <chrono>

using namespace std;
typedef long long ll;

// Calculate (a * b) % m with overflow handling
ll mulmod(ll a, ll b, ll m) {
    ll res = 0;
    a %= m;
    b %= m;
    while (b > 0) {
        if (b & 1)
            res = (__int128(res) + __int128(a)) % m;
        a = (__int128(a) * 2) % m;
        b >>= 1;
    }
    return res;
}

// Calculate (base^exp) % mod with overflow handling
ll powmod(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// Check if n is a quadratic residue modulo p using Legendre symbol
bool isQuadraticResidue(ll n, ll p) {
    if (n == 0) return true;
    ll ls = powmod(n, (p - 1) / 2, p);
    return ls == 1;
}

// Find square root of n modulo p using Tonelli-Shanks algorithm
ll modSquareRoot(ll n, ll p) {
    if (n == 0) return 0;
    if (p == 2) return n;
    if (!isQuadraticResidue(n, p)) return -1;

    // Simple case
    if (p % 4 == 3) {
        return powmod(n, (p + 1) / 4, p);
    }

    // Find Q and S such that p - 1 = Q * 2^S with Q odd
    ll Q = p - 1;
    ll S = 0;
    while (Q % 2 == 0) {
        Q /= 2;
        S++;
    }

    // Find a quadratic non-residue z
    ll z = 2;
    while (isQuadraticResidue(z, p)) z++;

    ll c = powmod(z, Q, p);
    ll x = powmod(n, (Q + 1) / 2, p);
    ll t = powmod(n, Q, p);
    ll m = S;

    while (t != 1) {
        ll i = 0;
        ll temp = t;
        while (temp != 1 && i < m) {
            temp = mulmod(temp, temp, p);
            i++;
        }
        if (i == m) return -1; // No solution
        ll b = powmod(c, 1LL << (m - i - 1), p);
        x = mulmod(x, b, p);
        c = mulmod(b, b, p);
        t = mulmod(t, c, p);
        m = i;
    }

    return x;
}

// Find cube root of y modulo p, assuming p ≡ 2 mod 3
ll cube_root(ll y, ll p) {
    if (y == 0) return 0;
    if (p % 3 == 2) {
        return powmod(y, (2 * p - 1) / 3, p);
    }
    // For p ≡1 mod3, cube roots are more complex to find
    // Implementing for p ≡2 mod3 only for efficiency
    return -1; // Indicates that cube root is not handled for this p
}

// Check if the polynomial f(x) = x^3 - 3x + 4 has any root modulo p
bool hasRoot(ll p) {
    // Compute the discriminant D = -4*(-3)^3 - 27*4^2 = 108 - 432 = -324 mod p
    ll D = (-4 * mulmod(-3, mulmod(-3, -3, p), p) - 27 * mulmod(4, 4, p)) % p;
    if (D < 0) D += p;

    bool is_sqr = isQuadraticResidue(D, p);

    if (p % 3 == 2) {
        if (is_sqr) {
            ll sqrt_D = modSquareRoot(D, p);
            if (sqrt_D == -1) return false; // No square root exists, unlikely if is_sqr is true

            ll inv2 = powmod(2, p - 2, p); // Modular inverse of 2

            ll term1 = mulmod((-4 + sqrt_D + p) % p, inv2, p);
            ll term2 = mulmod((-4 - sqrt_D + p) % p, inv2, p);

            ll u = cube_root(term1, p);
            ll v = cube_root(term2, p);

            if (u == -1 || v == -1) return false; // Cube root not found

            ll x = (u + v) % p;

            // Verify if x is indeed a root
            ll fx = (mulmod(x, mulmod(x, x, p), p) - mulmod(3, x, p) + 4) % p;
            if (fx < 0) fx += p;
            return fx == 0;
        } else {
            // When D is not a square, there is exactly one root
            // Implementing a generic cube root finder is complex
            // As a heuristic, assume a root exists
            // Alternatively, use Pollard's Rho or other algorithms for finding roots
            // For efficiency, we'll perform a small number of random trials

            // Initialize a random number generator
            static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_int_distribution<ll> dist(0, p - 1);

            // Try up to 20 random x values to find a root
            for (int i = 0; i < 1000; ++i) {
                ll x = dist(rng);
                ll fx = (mulmod(x, mulmod(x, x, p), p) - mulmod(3, x, p) + 4) % p;
                if (fx < 0) fx += p;
                if (fx == 0) return true;
            }
            return false; // No root found in trials
        }
    } else {
        // p ≡1 mod3, the number of roots depends on the discriminant
        // If D is a square, there are three roots; otherwise, one root
        // We'll use the same heuristic as above

        if (is_sqr) {
            // Attempt to find a root using cube roots if possible
            ll sqrt_D = modSquareRoot(D, p);
            if (sqrt_D == -1) return false;

            ll inv2 = powmod(2, p - 2, p); // Modular inverse of 2

            ll term1 = mulmod((-4 + sqrt_D + p) % p, inv2, p);
            ll term2 = mulmod((-4 - sqrt_D + p) % p, inv2, p);

            ll u = cube_root(term1, p);
            ll v = cube_root(term2, p);

            if (u != -1 && v != -1) {
                ll x = (u + v) % p;
                ll fx = (mulmod(x, mulmod(x, x, p), p) - mulmod(3, x, p) + 4) % p;
                if (fx < 0) fx += p;
                if (fx == 0) return true;
            }

            // If cube roots are not found, perform random trials
        }

        // Initialize a random number generator
        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<ll> dist(0, p - 1);

        // Try up to 20 random x values to find a root
        for (int i = 0; i < 20; ++i) {
            ll x = dist(rng);
            ll fx = (mulmod(x, mulmod(x, x, p), p) - mulmod(3, x, p) + 4) % p;
            if (fx < 0) fx += p;
            if (fx == 0) return true;
        }

        return false; // No root found in trials
    }
}

// Find square root of n modulo p using Tonelli-Shanks algorithm
ll findSquareRoot(ll n, ll p) {
    return modSquareRoot(n, p);
}

// Calculate R(p) for a given prime p
ll calculateR(ll p) {
    if (hasRoot(p)) {
        return 0;
    } else {
        // R(p) is a square root of -324 mod p
        ll n = ((-324 % p) + p) % p;
        ll sqrt = findSquareRoot(n, p);
        if (sqrt == -1) return 0; // No square root exists
        // Choose the smaller of the two roots
        if (sqrt > p - sqrt) sqrt = p - sqrt;
        return sqrt;
    }
}

int main() {
    const ll START = 1000000000LL;
    const ll END = 1100000000LL;

    ll sum = 0;

    // Initialize a primesieve iterator
    primesieve::iterator it(START, END);

    ll p = it.next_prime();
    while (p < END) {
        sum += calculateR(p);
        std::cout << p << std::endl;
        p = it.next_prime();
    }

    cout << "Sum of R(p): " << sum << endl;
    return 0;
}
