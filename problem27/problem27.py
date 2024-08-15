# Author: Bruce Hart <bruce.hart@gmail.com>

# Euler published the remarkable quadratic formula:
#
# n^2 + n + 41
#
# It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39.
# However, when n = 40, 40^2 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly
# when n = 41, 41^2 + 41 + 41 is clearly divisible by 41.
#
# Using computers, the incredible formula n^2 - 79n + 1601 was discovered, which produces 80 primes
# for the consecutive values n = 0 to 79. The product of the coefficients, -79 and 1601, is -126479.
#
# Considering quadratics of the form:
#
# n^2 + an + b, where |a| < 1000 and |b| < 1000
#
# where |n| is the modulus/absolute value of n
# e.g. |11| = 11 and |-4| = 4
#
# Find the product of the coefficients, a and b, for the quadratic expression that produces
# the maximum number of primes for consecutive values of n, starting with n = 0.

def isprime(x):
    if x <= 1:
        return False

    for n in range(2, int(x**0.5) + 1):
        if x % n == 0 and x != n:
            return False
    return True

def findPrimeLength(a, b):
    n = 0

    while isprime(n**2 + a*n + b):
        n += 1

    return n

def euler27():
    max_prime_length = 0
    max_prime_prod = 0

    for a in range(-1000, 1001):
        for b in range(-1000, 1001):
            l = findPrimeLength(a, b)
            if l > max_prime_length:
                max_prime_length = l
                max_prime_prod = a * b

    print(max_prime_prod)

if __name__ == '__main__':
    euler27()

