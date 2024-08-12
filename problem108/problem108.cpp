#include <iostream>
#include <cmath>

// This program finds the smallest positive integer n such that the equation 1/n = 1/x + 1/y has more than 1000 solutions in positive integers x and y, where x <= y.

// Function to calculate the number of divisors of n^2
int calculateDivisorsSquared(int number) {
  // Initialize the count of divisors to 1
  int divisorCount = 1;

  // Iterate from 2 to the square root of 'number' to find divisors
  for (int i = 2, end = static_cast<int>(sqrt(number)); i <= end; ++i) {
    // If 'i' is a divisor of 'number'
    if (number % i == 0) {
      // Initialize the exponent of 'i' to 0
      int exponent = 0;

      // Divide 'number' by 'i' repeatedly until it's no longer divisible by 'i'
      do {
        number /= i;
        ++exponent;
      } while (number % i == 0);

      // Update the divisor count based on the exponent of 'i'
      divisorCount *= (exponent * 2 + 1);

      // Recalculate the end of the loop as the square root of 'number' may have changed
      end = static_cast<int>(sqrt(number));
    }
  }

  // If 'number' is not 1, it means the largest prime factor is left
  if (number != 1) {
    // Multiply the divisor count by 3 to account for the largest prime factor
    divisorCount *= 3;
  }

  // Return the total number of divisors of n^2
  return divisorCount;
}

// Function to find the smallest n such that the equation has more than 1000 solutions
int findSmallestN() {
  // Iterate over positive integers starting from 1
  for (int n = 1; ; ++n) {
    // If the number of divisors of n^2 divided by 2 plus 1 is greater than 1000
    if ((calculateDivisorsSquared(n) + 1) / 2 > 1000) {
      // Return the value of n
      return n;
    }
  }
}

int main() {
  // Find the smallest n and print it to the console
  std::cout << findSmallestN() << std::endl;
  return 0;
}