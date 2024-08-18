#include <iostream>
#include <numeric>
#include <vector>

// Function to calculate the GCD of two numbers
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to calculate the LCM of two numbers
long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

// Function to calculate the LCM of a range of numbers
long long lcm_range(int start, int end) {
    long long result = start;
    for (int i = start + 1; i <= end; ++i) {
        result = lcm(result, i);
    }
    return result;
}

int main() {
    int start = 2, end = 80;
    long long result = lcm_range(start, end);
    
    std::cout << "LCM of numbers from " << start << " to " << end << " is: " << result << std::endl;
    return 0;
}

