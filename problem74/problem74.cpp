#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Factorial lookup table
int factorials[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

// Function to calculate the sum of factorial of digits of a number
int sumOfFactorialOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += factorials[num % 10];
        num /= 10;
    }
    return sum;
}

// Function to find the length of the chain for a given starting number
int findChainLength(int start) {
    std::unordered_set<int> seen;
    int current = start;
    while (seen.find(current) == seen.end()) {
        seen.insert(current);
        current = sumOfFactorialOfDigits(current);
    }
    return seen.size();
}

int main() {
    int count = 0;
    for (int i = 1; i < 1000000; ++i) {
        if (findChainLength(i) == 60) {
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}
