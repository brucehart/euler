#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

const int LIMIT = 1000000;

// Function to calculate the sum of proper divisors of a number
int sumOfProperDivisors(int n) {
    int sum = 1; // 1 is always a proper divisor
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            if (i * i == n) {
                sum += i;
            } else {
                sum += i + n / i;
            }
        }
    }
    return sum;
}

int main() {
    std::vector<int> divisorSum(LIMIT + 1, 0);
    std::unordered_map<int, int> chainLength;

    // Precompute the sum of proper divisors for each number
    for (int i = 1; i <= LIMIT; ++i) {
        divisorSum[i] = sumOfProperDivisors(i);
    }

    int maxLength = 0;
    int smallestMember = 0;

    // Find the longest amicable chain
    for (int i = 1; i <= LIMIT; ++i) {
        std::unordered_map<int, int> visited;
        int current = i;
        int length = 0;
        bool validChain = true;

        while (true) {
            if (current > LIMIT || visited.count(current) > 0) {
                validChain = false;
                break;
            }

            visited[current] = length++;
            current = divisorSum[current];

            if (current == i) {
                break;
            }
        }

        if (validChain) {
            int chainStart = i;
            for (const auto& pair : visited) {
                if (pair.second >= visited[current]) {
                    chainStart = std::min(chainStart, pair.first);
                }
            }

            if (length > maxLength) {
                maxLength = length;
                smallestMember = chainStart;
            }
        }
    }

    std::cout << smallestMember << std::endl;

    return 0;
}
