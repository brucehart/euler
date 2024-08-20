#include <iostream>

int main() {
    // Initialize the first two values of L
    long long L0 = 1;
    long long L1 = 17;
    long long sum = 0;

    // Start calculating L_n using the recurrence relation
    for (int n = 2; n <= 12; ++n) {
        long long Ln = 18 * L1 - L0;
        sum += L1;  // Sum up L from L1 to L12
        L0 = L1;    // Update L0 to be the previous L1
        L1 = Ln;    // Update L1 to be the current L_n
    }

    // Add L12 to the sum
    sum += L1;

    // Print the result
    std::cout << sum << std::endl;

    return 0;
}

