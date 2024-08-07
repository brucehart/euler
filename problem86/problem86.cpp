#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

// Function to calculate combinations
int combinations(int a, int bc) {
    if (2 * a < bc) {
        return 0;
    } else if (a >= bc) {
        return (bc / 2);
    } else {
        if (bc % 2 == 0) {
            return a + 1 - (bc / 2);
        } else {
            return a - ((bc - 1) / 2);
        }
    }
}

// Function to generate Pythagorean Triplets and find the result
int solve_triplets(int N) {
    const int limit = 10000;
    std::vector<int> triples(limit + 1, 0);
    
    for (int m = 1; m <= std::sqrt(2 * limit); ++m) {
        for (int n = 1; n < m; ++n) {
            if ((m + n) % 2 == 1 && std::gcd(m, n) == 1) {
                int b = m * m - n * n;
                int c = 2 * m * n;
                
                // Case 1
                for (int k = 1; k * b <= limit; ++k) {
                    triples[k * b] += combinations(k * b, k * c);
                }
                
                // Case 2
                for (int k = 1; k * c <= limit; ++k) {
                    triples[k * c] += combinations(k * c, k * b);
                }
            }
        }
    }
    
    int total = 0;
    for (size_t x = 0; x < triples.size(); ++x) {
        total += triples[x];
        if (total > N) {
            return x;
        }
    }

    return -1; // Return -1 if the condition is never met
}

int main() {
    int k = 1000000;
    int result = solve_triplets(k);
    std::cout << result << std::endl;

    return 0;
}
