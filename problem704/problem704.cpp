#include <iostream>
#include <cmath>

// Function to calculate S2(N) - count of bits in base 2
unsigned long long S2(unsigned long long N) {
    unsigned long long count = 0;

    while (N > 0) {
        count += N & 1; 
        N >>= 1; 
    }

    return count;
}

// Main function to calculate S(N)
unsigned long long S(unsigned long long N) {
    unsigned long long log2_floor = std::floor(std::log2(N + 1)); 

    unsigned long long term1 = (N + 2) * log2_floor; 

    unsigned long long term2 = 2 * (std::pow(2, log2_floor) - 1);

    unsigned long long term3 = N + 1 - S2(N + 1);

    return term1 - term2 - term3;
}

int main() {
    unsigned long long N = 10000000000000000ULL;

    unsigned long long result = S(N); 
    std::cout << result << std::endl;

    return 0;
}