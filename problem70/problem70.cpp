#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

// Function to calculate the Euler's Totient function φ(n)
int phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// Function to check if two numbers are permutations of each other
bool arePermutations(int a, int b) {
    string strA = to_string(a);
    string strB = to_string(b);
    sort(strA.begin(), strA.end());
    sort(strB.begin(), strB.end());
    return strA == strB;
}

int main() {
    const int LIMIT = 10000000;
    double minRatio = numeric_limits<double>::max();
    int result = 0;

    for (int n = 2; n < LIMIT; ++n) {
        int phiN = phi(n);
        if (arePermutations(n, phiN)) {
            double ratio = static_cast<double>(n) / phiN;
            if (ratio < minRatio) {
                minRatio = ratio;
                result = n;
            }
        }
    }

    cout << result << endl;
    return 0;
}
