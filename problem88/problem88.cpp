#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>

// Constant representing the limit for the problem
const int LIMIT = 12000;

// Vector to store the minimum sum-product numbers for each k
std::vector<int> minSumProduct;

/**
 * Recursively calculates all factorizations of the integer n >= 2 
 * and updates smaller solutions into minSumProduct.
 * 
 * @param n The original number being factorized.
 * @param remain The remaining product to factorize.
 * @param maxFactor The maximum factor to consider.
 * @param sum The current sum of the factors.
 * @param terms The number of terms in the current factorization.
 */
void factorize(int n, int remain, int maxFactor, int sum, int terms) {
    // Base case: if the remaining product is 1, we have a valid factorization
    if (remain == 1) {
        if (sum > n) {
            throw std::logic_error("Sum exceeds product without using factors of 1");
        }

        // Adjust the number of terms and update minSumProduct if necessary
        terms += n - sum;
        if (terms <= LIMIT && n < minSumProduct[terms]) {
            minSumProduct[terms] = n;
        }
    } else {
        // Recursive case: factorize the remaining product
        for (int i = 2; i <= maxFactor; ++i) {
            if (remain % i == 0) {
                int factor = i;
                factorize(n, remain / factor, std::min(factor, maxFactor), sum + factor, terms + 1);
            }
        }
    }
}

int main() {
    // Initialize minSumProduct with large values
    minSumProduct.assign(LIMIT + 1, INT_MAX);

    // Factorize each number from 2 to LIMIT*2
    for (int i = 2; i <= LIMIT * 2; ++i) {
        factorize(i, i, i, 0, 0);
    }

    // Eliminate duplicates and compute the sum of unique minSumProduct values
    std::set<int> items;
    for (int i = 2; i < minSumProduct.size(); ++i) {
        items.insert(minSumProduct[i]);
    }
    int sum = 0;
    for (int n : items) {
        sum += n;
    }

    // Output the result
    std::cout << sum << std::endl;
    return 0;
}
