#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Function to compute the radical of a number
int radical(int n) {
    int rad = 1;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            rad *= p;
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) { // If there is a prime factor greater than sqrt(n)
        rad *= n;
    }
    return rad;
}

int main() {
    const int limit = 100000;
    std::vector<std::pair<int, int>> radicals;

    // Calculate radicals and store them with their respective numbers
    for (int i = 1; i <= limit; ++i) {
        radicals.emplace_back(radical(i), i);
    }

    // Sort the vector of pairs
    std::sort(radicals.begin(), radicals.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    });

    // Output the 10000th element in the sorted list
    std::cout << radicals[9999].second << std::endl;

    return 0;
}
