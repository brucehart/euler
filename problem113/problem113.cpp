#include <iostream>

long long nChooseR(int n, int r) {
    long long value = 1;
    for (int x = 0; x < r; ++x) {
        value *= (n - x);
        value /= (x + 1);
    }
    return value;
}

int main() {
    int n = 100;

    long long increasing = nChooseR(n + 9, 9) - 1;
    long long decreasing = nChooseR(n + 10, 10) - 1;
    std::cout << (increasing + decreasing - 10 * n) << std::endl;

    return 0;
}
