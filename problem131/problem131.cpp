#include <iostream>
#include <cmath>

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    const int LIMIT = 1000000;
    int count = 0;

    // Iterate over possible values of a
    for (int a = 1;; ++a) {
        int p = 3 * a * a + 3 * a + 1;

        if (p >= LIMIT) break; // Stop if p exceeds one million

        if (isPrime(p)) {
            ++count;
        }
    }

    std::cout << count << std::endl;
    return 0;
}
