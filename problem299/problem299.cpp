#include <iostream>

// Define the limit
const long long LIMIT = 100000000;

// Function to calculate the greatest common divisor (GCD)
long long calculate_gcd(long long a, long long b) {
    // Ensure a >= b
    if (a < b) {
        long long temp = a;
        a = b;
        b = temp;
    }
    
    long long remainder = a % b;
    if (remainder == 0) {
        return b;
    } else {
        return calculate_gcd(b, remainder);
    }
}

// Function to handle the incenter case
long long count_incenter_case() {
    long long count = 0;
    
    // Iterate over n from 1 to LIMIT/2 - 1
    for (long long n = 1; n < LIMIT / 2; n++) {
        // Iterate over m from 1 to n - 1
        for (long long m = 1; m < n; m++) {
            // Skip if m + n is even
            if ((m + n) % 2 == 0) continue;
            
            // Skip if gcd(m, n) is not 1
            if (calculate_gcd(m, n) != 1) continue;
            
            long long b = n * n - m * m;
            long long d = 2 * n * m;
            long long sum = b + d;
            
            // Break if the sum is greater than or equal to LIMIT
            if (sum >= LIMIT) break;
            
            // Update the count based on the values of b and d
            if (b == d) {
                count += LIMIT / sum;
            } else {
                count += 2 * (LIMIT / sum);
            }
        }
    }
    
    return count;
}

// Function to handle the parallel case
long long count_parallel_case() {
    long long count = 0;
    
    // Iterate over n from 1 to LIMIT - 1, incrementing by 2
    for (long long n = 1; n < LIMIT; n += 2) {
        // Iterate over m from 1 to LIMIT - 1
        for (long long m = 1; m < LIMIT; m++) {
            // Skip if gcd(m, n) is not 1
            if (calculate_gcd(m, n) != 1) continue;
            
            long long g = 2 * n * m;
            long long a = n * n + 2 * m * m;
            long long b = g + a;
            
            // Break if b is greater than LIMIT / 2
            if (b > LIMIT / 2) break;
            
            // Update the count
            count += (LIMIT - 1) / (2 * b);
        }
    }
    
    return count;
}

// Main function to calculate the total count and print the result
int main() {
    long long result = count_incenter_case() + count_parallel_case();
    std::cout << result << std::endl;
    
    return 0;
}

