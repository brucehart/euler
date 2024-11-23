#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

// Function to compute f(x) = x^3 - 3x + 4 mod p
ll f(ll x, ll p) {
    x = x % p;
    ll x3 = (x * x % p) * x % p;
    ll fx = (x3 - 3 * x + 4) % p;
    if (fx < 0) fx += p;
    return fx;
}

// Function to compute R(p) = product_{x=0}^{p-1} f(x) mod p
ll computeR(ll p) {
    ll R = 1 % p;  // Initialize R to 1 modulo p
    for (ll x = 0; x < p; x++) {
        ll fx = f(x, p);
        R = (R * fx) % p;
    }
    return R;
}

int main() {
    // Generate a list of primes up to 1000 using the Sieve of Eratosthenes
    const int MAX_P = 1000;
    vector<bool> is_prime(MAX_P + 1, true);
    is_prime[0] = is_prime[1] = false;
    vector<int> primes;
    for (int i = 2; i <= MAX_P; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAX_P; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Compute and print R(p) for each prime p
    for (size_t idx = 0; idx < primes.size(); idx++) {
        int p = primes[idx];
        ll R = computeR(p);
        cout << "R(" << p << ") = " << R << " | " << p % 5 <<endl;
    }

    return 0;
}
