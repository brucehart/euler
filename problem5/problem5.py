# Author: Bruce Hart
# Email: bruce.hart@gmail.com

# Problem Description:
# 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
# What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

import math

def lcm(a, b):
    """Return the least common multiple of a and b."""
    return abs(a*b) // math.gcd(a, b)

def smallest_mult(n):
    """Return the smallest number that is evenly divisible by all numbers from 1 to n."""
    result = 1
    for i in range(1, n + 1):
        result = lcm(result, i)
    return result

if __name__ == '__main__':
    # Calculate the smallest multiple for numbers 1 through 20
    result = smallest_mult(20)
    print(result)

