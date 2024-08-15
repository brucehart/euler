# Author: Bruce Hart <bruce.hart@gmail.com>

# Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
#
# 1634 = 1^4 + 6^4 + 3^4 + 4^4
# 8208 = 8^4 + 2^4 + 0^4 + 8^4
# 9474 = 9^4 + 4^4 + 7^4 + 4^4
#
# As 1 = 1^4 is not a sum it is not included.
#
# The sum of these numbers is 1634 + 8208 + 9474 = 19316.
#
# Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

def sumMatch(n, p):
    # Check if sum of p-th powers of its digits equals the number
    return sum(int(x) ** p for x in str(n)) == n

def euler30():
    N = 10**6  # Upper bound for the search
    P = 5  # Power to raise digits
    # Using list comprehension to filter numbers matching the condition
    print(sum(x for x in range(2, N+1) if sumMatch(x, P)))

if __name__ == '__main__':
    euler30()

