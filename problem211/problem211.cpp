#include <iostream>
#include <cmath>
#include <vector>

int main() {
    const int limit = 64000000;
    std::vector<long long> sigma2(limit, 1);  // Initialize the array with 1
    
    // Iterate over each k from 2 to limit
    for (int k = 2; k < limit; ++k) {
        long long k_squared = static_cast<long long>(k) * k;
        for (int multiple = k; multiple < limit; multiple += k) {
            sigma2[multiple] += k_squared;
        }
    }
    
    long long sum = 0;
    
    // Iterate over the array and sum up the elements that are perfect squares
    for (int n = 1; n < limit; ++n) {
        long long value = sigma2[n];
        long long root = static_cast<long long>(std::sqrt(value));
        if (root * root == value) {
            sum += n;
        }
    }
    
    std::cout << sum << std::endl;
    
    return 0;
}
