#include <iostream>
#include <string>

// Recursive function to solve the problem
std::string solve(long long p, long long q) {
    // Base case: if q is 0, return an empty string
    if (q == 0)    
        return "";

    std::string res = ""; // Result string to accumulate results

    if (p > q) {
        // Case where p > q: calculate remainder of (p - 1) % q + 1
        long long p2 = (p - 1) % q + 1;
        // Recursive call for the remainder
        res += solve(p2, q);
        // Append the result of integer division (p - p2) / q
        res += std::to_string((p - p2) / q) + ",";
    } else {
        // Case where p <= q: calculate remainder of q % p
        long long q2 = q % p;
        // Recursive call for the remainder
        res += solve(p, q2);
        // Append the result of integer division (q - q2) / p
        res += std::to_string((q - q2) / p) + ",";
    }

    return res;   
}

// Function to compute the greatest common divisor (GCD) of two numbers
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long long p = 123456789ll; // Numerator
    long long q = 987654321ll; // Denominator

    // Simplify the fraction by dividing by the GCD
    long long g = gcd(p, q);
    p /= g;
    q /= g;

    // Solve and remove the trailing comma from the result
    std::string result = solve(p, q);
    if (!result.empty())
        result.pop_back(); // Remove the trailing comma

    // Output the result
    std::cout << result << std::endl;

    return 0;
}
