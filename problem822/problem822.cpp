#include <iostream>
#include <vector>
#include <algorithm>

// Define a type alias for convenience
typedef long long ll;

// Function to compute (base^exponent) % mod using fast exponentiation
ll powmod(ll base, ll exponent, ll mod) {
    ll result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1) { // If the least significant bit is set
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // Square the base
        exponent >>= 1; // Shift right by 1 bit
    }
    return result;
}

// Function S as defined in the Python code
ll S(ll n, ll m, ll mod = 1234567891) {
    // Initialize vector A with values from 2 to n inclusive
    std::vector<ll> A;
    A.reserve(n - 1);
    for (ll i = 2; i <= n; ++i) {
        A.push_back(i);
    }

    ll k = 0;

    // Continue replacing the minimum element with its square until min^2 >= max
    while (true) {
        ll min_A = *std::min_element(A.begin(), A.end());
        ll max_A = *std::max_element(A.begin(), A.end());

        if (min_A * min_A >= max_A) {
            break;
        }

        // Find the index of the first occurrence of the minimum element
        auto it = std::min_element(A.begin(), A.end());
        ll index = std::distance(A.begin(), it);

        // Replace the minimum element with its square
        A[index] = min_A * min_A;
        k += 1;
    }

    // Sort the vector A
    std::sort(A.begin(), A.end());

    ll total = 0;
    ll m_k = m - k;
    ll q = m_k / (n - 1);
    ll r = m_k % (n - 1);

    // Iterate through the sorted vector and compute the total
    for (size_t i = 0; i < A.size(); ++i) {
        ll exponent;
        if (static_cast<ll>(i) < r) {
            exponent = powmod(2, q + 1, mod - 1);
        } else {
            exponent = powmod(2, q, mod - 1);
        }
        total = (total + powmod(A[i], exponent, mod)) % mod;
    }

    return total;
}

int main() {
    ll a = 10000;
    ll b = 10000000000000000;

    // Compute and print the result of S(a, b)
    std::cout << S(a, b) << std::endl;

    return 0;
}
