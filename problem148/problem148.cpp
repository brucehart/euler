#include <iostream>
#include <vector>

// Function to calculate the number of entries in a row of Pascal's Triangle
// that are not divisible by 7
unsigned long long count_non_divisible_entries(unsigned long long n) {
    unsigned long long count = 1;
    while (n > 0) {
        count *= (n % 7) + 1;
        n /= 7;
    }
    return count;
}

int main() {
    unsigned long long N = 1000000000LL; // 10^9
    unsigned long long result = 0;
    
    for (unsigned long long i = 0; i < N; ++i) {
        result += count_non_divisible_entries(i);
    }
    
    std::cout << result << std::endl;
    
    return 0;
}
