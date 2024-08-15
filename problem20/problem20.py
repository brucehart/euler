# Author: Bruce Hart <bruce.hart@gmail.com>

# n! means n * (n - 1) * ... * 3 * 2 * 1
#
# For example, 10! = 10 * 9 * ... * 3 * 2 * 1 = 3628800,
# and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
#
# Find the sum of the digits in the number 100!

from functools import reduce

def genDigits():
    seed = reduce(lambda x, y: x * y, range(1, 101))
    
    while seed > 0:
        r = seed % 10
        seed //= 10
        yield r

def euler20():
    print(sum(genDigits()))

if __name__ == '__main__':
    euler20()

