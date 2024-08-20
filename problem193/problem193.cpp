#include <iostream>
#include <vector>
#include <cmath>

long long S1(long long N) {
    long long sqrtN = static_cast<long long>(std::sqrt(N));
    std::vector<long long> a(sqrtN + 1, 1);
    a[0] = 0;  

    for (long long i = sqrtN; i >= 2; --i) {
        a[i] = N / (i * i);
        for (long long j = 2; j <= sqrtN / i; ++j) {
            a[i] -= a[i * j];
        }
    }

    long long sum_a = 0;
    for (long long i = 1; i <= sqrtN; ++i) {
        sum_a += a[i];
    }

    return N + 1 - sum_a;
}

int main() {
    long long N = pow(2,50);
    std::cout << S1(N) << std::endl;

    return 0;
}

