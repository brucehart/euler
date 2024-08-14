# Author: Bruce Hart
# Email: bruce.hart@gmail.com

# Problem Description:
# The sum of the squares of the first ten natural numbers is,
# 1^2 + 2^2 + ... + 10^2 = 385
#
# The square of the sum of the first ten natural numbers is,
# (1 + 2 + ... + 10)^2 = 55^2 = 3025
#
# Hence the difference between the sum of the squares of the first ten natural numbers
# and the square of the sum is 3025 - 385 = 2640.
#
# Task:
# Find the difference between the sum of the squares of the first one hundred natural numbers
# and the square of the sum.

def euler6():
    D = 100
    # In Python 3, range is used instead of xrange.
    n = range(1, D+1)

    # Using a generator expression for sum of squares
    sum_squares = sum(x**2 for x in n)
    # Calculating the square of the sum
    square_sum = sum(n) ** 2

    # Calculate the difference
    diff = square_sum - sum_squares

    print(diff)

if __name__ == '__main__':
    euler6()

