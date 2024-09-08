#include <iostream>
#include <vector>

int main() {
    int N = 10000000;  // Define the upper limit for numbers to check divisors
    int count = 0;     // Initialize a counter to count pairs of consecutive numbers with equal divisors
    
    // Create a vector to store the number of divisors for each number from 1 to N
    // Initialize all values to 0
    std::vector<int> numDivisors(N + 1, 0);

    // Loop through each number i from 1 to N
    for (int i = 1; i <= N; i++) {
        int j = 1;  // Initialize multiplier j
        // For each i, increment the divisor count for all multiples of i (i * j <= N)
        while (j * i <= N) {
            numDivisors[j * i]++;  // Increment divisor count for the number j * i
            j++;                   // Move to the next multiple
        }        
    }

    // Loop through the numbers from 1 to N-1
    // Compare the number of divisors of each number with the next consecutive number
    for (int k = 1; k < N; k++) {
        // If the number of divisors of k and k+1 are the same, increment the counter
        if (numDivisors[k] == numDivisors[k + 1]) {
            count++;
        }
    }

    // Output the total count of consecutive numbers with equal number of divisors
    std::cout << count << std::endl;

    return 0;
}
