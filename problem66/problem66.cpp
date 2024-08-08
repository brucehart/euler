#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <cmath>

// Function to solve Pell's equation using continued fraction method
mpz_class solvePell(int D) {
    mpz_class m = 0;
    mpz_class d = 1;
    mpz_class a0 = sqrt(D);
    mpz_class a = a0;

    if (a0 * a0 == D) {
        return 0; // Perfect square case
    }

    mpz_class num1 = 1;
    mpz_class num2 = a;
    mpz_class den1 = 0;
    mpz_class den2 = 1;

    mpz_class h1 = 1, h2 = a0;
    mpz_class k1 = 0, k2 = 1;

    while (true) {
        m = d * a - m;
        d = (D - m * m) / d;
        a = (a0 + m) / d;

        mpz_class h = a * h2 + h1;
        mpz_class k = a * k2 + k1;

        h1 = h2;
        h2 = h;
        k1 = k2;
        k2 = k;

        if (h * h - D * k * k == 1) {
            return h;
        }
    }
}

void solve() {
    const int DMAX = 1000;
    mpz_class x;

    // Values of solution x and D at maximum
    mpz_class xmax = 0;
    int Dmax = 0;

    for (int D = 1; D <= DMAX; D++) {
        x = solvePell(D);
        if (x > xmax) {
            xmax = x;
            Dmax = D;
        }
        //std::cout << "D = " << D << ", x = " << x << std::endl;
    }
    std::cout << Dmax << std::endl;
}

int main() {
    solve();
    return 0;
}
