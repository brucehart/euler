#include <iostream>
#include <cmath>
#include <unordered_set>

// Function to check if a number is a perfect square
bool isPerfectSquare(long long number) {
    long long squareRoot = static_cast<long long>(std::sqrt(number));
    return squareRoot * squareRoot == number;
}

// Function to compute the sum of all progressive squares below the given limit
long long calculateSumOfProgressiveSquares(long long upperLimit) {
    std::unordered_set<long long> uniqueProgressiveSquares;
    
    // Iterate over potential values for z (the cube component)
    for (long long zValue = 2; zValue * zValue * zValue <= upperLimit; ++zValue) {
        // Iterate over potential values for y (the square component)
        for (long long yValue = 1; yValue < zValue; ++yValue) {
            // Early exit if the current combination exceeds the limit
            if (zValue * zValue * zValue * yValue + yValue * yValue > upperLimit) {
                break;
            }
            
            // Iterate over potential values for x (the linear component)
            for (long long xValue = 1; xValue * yValue * zValue * zValue * zValue <= upperLimit; ++xValue) {
                // Calculate the candidate number n based on x, y, and z
                long long candidateNumber = zValue * zValue * zValue * xValue * xValue * yValue + xValue * yValue * yValue;
                
                // If the candidate number exceeds the limit, break the loop
                if (candidateNumber > upperLimit) {
                    break;
                } else {
                    // Check if the candidate number is a perfect square
                    if (isPerfectSquare(candidateNumber)) {
                        // Add it to the set of unique progressive squares
                        uniqueProgressiveSquares.insert(candidateNumber);
                    }
                }
            }
        }
    }
    
    // Calculate the sum of all unique progressive squares
    long long sumOfSquares = 0;
    for (const auto& progressiveSquare : uniqueProgressiveSquares) {
        sumOfSquares += progressiveSquare;
    }
    
    return sumOfSquares;
}

int main() {
    long long limit = 1000000000000LL; // 10^12
    long long result = calculateSumOfProgressiveSquares(limit);
    
    std::cout << result << std::endl;
    
    return 0;
}
