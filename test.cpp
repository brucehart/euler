#include <iostream>
using namespace std;

const int MOD = 1000000007;

int main() {
    int n = 10000000; // Given n = 10^7
    int a = 1, b = 1, c = 2, d;

    for (int i = 3; i <= n; ++i) {
        d = ((long long)a + b + c) % MOD;
        a = b;
        b = c;
        c = d;
    }

    cout << c << endl;
    return 0;
}

