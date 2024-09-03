#include <iostream>
#include <vector>
#include <cmath>
#include <set>

// Function to calculate Pisano period for n
unsigned long long pisanoPeriod(unsigned long long n) {
    unsigned long long previous = 0;
    unsigned long long current = 1;
    unsigned long long period = 0;

    for (unsigned long long i = 0; i < n * n; i++) {
        unsigned long long temp = current;
        current = (previous + current) % n;
        previous = temp;

        if (previous == 0 && current == 1) {
            period = i + 1;
            break;
        }
    }
    return period;
}

// Function to recursively generate the products of combinations
void generateProducts(const std::vector<int>& values, int index, unsigned long long currentProduct, std::set<unsigned long long>& productSet) {
    if (index == values.size()) {
        productSet.insert(currentProduct);
        return;
    }
    
    // Two choices: include the current value in the product or skip it
    generateProducts(values, index + 1, currentProduct * values[index], productSet);  // Include
    generateProducts(values, index + 1, currentProduct, productSet);  // Skip
}

// Function to generate the set of products
std::set<unsigned long long> generateProductSet(const std::vector<int>& values) {
    std::set<unsigned long long> productSet;
    generateProducts(values, 0, 1, productSet);
    return productSet;
}

int main() {    
    //prime factors of F_121 - 1 that are less than 10^9
    //Since F_1 = 1 and F_1 mod x = F_121 mod x then F_121 mod x = 1 or (F_121 - 1) mod x = 0
    std::vector<int> values = {2, 2, 2, 2, 3, 3, 5, 11, 31, 41, 61, 2521};    
    std::set<unsigned long long> productSet = generateProductSet(values);
    unsigned long long ten_ninth = pow(10, 9);
    unsigned long long valueSum = 0;

    for(auto product : productSet) {
        if (product < ten_ninth && pisanoPeriod(product) == 120)
            valueSum += product;
    }

    std::cout << valueSum << std::endl;

    return 0;
}

