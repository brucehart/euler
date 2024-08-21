#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <gmpxx.h>

// Function to perform modular multiplication
mpz_class mulmod(const mpz_class& a, const mpz_class& b, const mpz_class& MOD) {
    return (a * b) % MOD;
}

// Function to perform modular inverse
mpz_class invmod(const mpz_class& a, const mpz_class& MOD) {
    mpz_class inv;
    mpz_invert(inv.get_mpz_t(), a.get_mpz_t(), MOD.get_mpz_t());
    return inv;
}

// Function to factorize a number using trial division (for simplicity)
std::vector<std::pair<mpz_class, int>> factorize(int n) {
    std::vector<std::pair<mpz_class, int>> factors;
    for (int i = 2; i <= sqrt(n); i++) {
        int count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count > 0) {
            factors.emplace_back(i, count);
        }
    }
    if (n > 1) {
        factors.emplace_back(n, 1);
    }
    return factors;
}

mpz_class F(int64_t N, const mpz_class& MOD) {
    std::map<mpz_class, int64_t> table;
    mpz_class total = 0;
    mpz_class partial = 1;

    for (int64_t k = 2; k <= N; k++) {
        mpz_class old = 1;

        auto factors = factorize(k);
        for (const auto& factor : factors) {
            const mpz_class& p = factor.first;
            int e = factor.second;

            if (table.find(p) != table.end()) {
                old = mulmod(old, 2 * table[p] + 1, MOD);
            } else {
                table[p] = 0;
            }

            table[p] += e;
            partial = mulmod(partial, 2 * table[p] + 1, MOD);
        }

        partial = mulmod(partial, invmod(old, MOD), MOD);
        total += partial;
        total %= MOD;
    }

    return total;
}

int main() {
    const mpz_class MOD = 1000000087;

    int64_t N = pow(10, 7);
    mpz_class result = F(N, MOD);
    std::cout << result << std::endl;    

    return 0;
}

