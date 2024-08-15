# -*- coding: utf-8 -*-
# Author: Bruce Hart <bruce.hart@gmail.com>

# 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
#
# Find the sum of all numbers which are equal to the sum of the factorial of their digits.
#
# Note: as 1! = 1 and 2! = 2 are not sums they are not included.

fact = [0]*100  # Precompute factorials to speed up calculations

def initialize_factorials():
    fact[0] = 1  # 0! is 1

    for n in range(1, len(fact)):
        fact[n] = fact[n-1] * n  # Compute n! from (n-1)!

def factorial(x):
    return fact[x]  # Return precomputed factorial

def factorial_sum(x):
    return sum(factorial(int(digit)) for digit in str(x))  # Sum of factorials of digits

def euler34():
    matches = []  # List to hold numbers meeting the condition
    initialize_factorials()  # Initialize factorial values
    maxN = factorial(9) * 7  # Upper limit based on 7 * 9! (largest sum of 7 digit numbers)

    for i in range(3, maxN + 1):  # Start from 3 because 1 and 2 are not sums
        if factorial_sum(i) == i:  # Check if number is equal to sum of the factorial of its digits
            matches.append(i)

    print(sum(matches))  # Print the sum of all numbers meeting the condition

if __name__ == '__main__':
    euler34()  # Run the function

