# Author: Bruce Hart <bruce.hart@gmail.com>

# The prime factors of 13195 are 5, 7, 13, and 29.
#
# What is the largest prime factor of the number 600851475143?

def isprime(x):
    # Check if a number is prime
    for n in range(2, int(x**0.5) + 1):
        if x % n == 0 and x != n:
            return False
    return True

def euler3():
    D = 600851475143
    # Generate possible factors up to the square root of D
    factors = range(2, int(D**0.5) + 1)
    # Filter factors to only include divisors of D
    factors = filter(lambda x: D % x == 0, factors)
    # Further filter to include only prime factors
    factors = filter(isprime, factors)
    
    # Print the maximum prime factor found
    print(max(factors))

if __name__ == '__main__':
    euler3()

