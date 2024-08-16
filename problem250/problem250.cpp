#include <iostream>
#include <vector>
#include <cmath>

const long long MOD = 10000000000000000LL;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    std::vector<long long> subsetCounts(250, 0);
    subsetCounts[0] = 1;  // Start with the empty subset

    for (int i = 1; i <= 250250; i++) {
        int currentPower = modPow(i, i, 250);
        std::vector<long long> newSubsetCounts(250, 0);

        // Update the number of subsets with each possible sum modulo 250
        for (int j = 0; j < 250; j++) {
            newSubsetCounts[(j + currentPower) % 250] = (subsetCounts[j] + subsetCounts[(j + currentPower) % 250]) % MOD;
        }

        subsetCounts = newSubsetCounts;  // Move to the new state
    }

    // The result is the number of subsets with a sum modulo 250 equal to 0, minus the empty subset
    std::cout << (subsetCounts[0] - 1 + MOD) % MOD << std::endl;

    return 0;
}
