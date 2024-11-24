#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

// Check if number is prime
bool isPrime(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Calculate (a * b) % m with overflow handling
ll mulmod(ll a, ll b, ll m) {
    ll res = 0;
    a %= m;
    while (b > 0) {
        if (b & 1)
            res = (res + a) % m;
        a = (a + a) % m;
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

// Find cubic root of n modulo p if it exists
ll findCubicRoot(ll n, ll p) {
    if (n == 0) return 0;
    
    // If p ≡ 2 (mod 3), we can use the formula x = n^((2p-1)/3)
    if (p % 3 == 2) {
        return powmod(n, (2 * p - 1) / 3, p);
    }
    
    // For p ≡ 1 (mod 3), we would need to implement a more complex algorithm
    // But for this specific problem, we don't need it as we're just checking existence
    return -1;
}

// Calculate R(p) for a given prime p
ll calculateR(ll p) {
    // Handle the discriminant approach directly
    // Discriminant of x^3 - 3x + 4 is -324 = -4 * 3^4
    ll n = ((-324 % p + p) % p);
    
    // For a cubic x^3 + ax^2 + bx + c
    // Discriminant = -27a^2c^2 + 9abc + 2a^3c - a^2b^2 - 4b^3
    // For our case x^3 - 3x + 4, a=0, b=-3, c=4
    // D = 0 - 0 + 0 - 0 - 4(-3)^3 = -4(-27) = 108
    // D = -324
    
    // Calculate the Legendre symbol of n
    ll legendre = powmod(n, (p - 1) / 2, p);
    
    // If n is a quadratic residue
    if (legendre == 1) {
        // If p ≡ 3 (mod 4), we can use a simpler formula
        if (p % 4 == 3) {
            ll sqrt = powmod(n, (p + 1) / 4, p);
            // Choose the smaller square root
            return sqrt <= p/2 ? sqrt : p - sqrt;
        }
        
        // For p ≡ 1 (mod 4), use quadratic reciprocity
        // In this case, we can determine which root to choose based on 
        // additional criteria specific to our polynomial
        ll t = (p + 1) / 4;
        ll sqrt = powmod(n, t, p);
        return sqrt <= p/2 ? sqrt : p - sqrt;
    }
    
    return 0;  // Case where polynomial is reducible
}

int main() {
    const ll START = 1000000000LL;
    const ll END = 1100000000LL;
    
    ll sum = 0;
    for (ll p = START; p <= END; p++) {
        if (isPrime(p)) {
            sum = (sum + calculateR(p));
            std::cout << p << std::endl;
        }
    }
    
    cout << "Sum of R(p): " << sum << endl;
    return 0;
}