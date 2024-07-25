# We need to solve the problem of finding the sum of the first 50 reversible prime squares.
# A reversible prime square is defined by the following criteria:
# 1. It is not a palindrome.
# 2. It is the square of a prime.
# 3. Its reverse is also the square of a prime.

from sympy import isprime
import numpy as np

def is_palindrome(n):
    return str(n) == str(n)[::-1]

def reverse_number(n):
    return int(str(n)[::-1])

# Function to find the first 50 reversible prime squares
def find_reversible_prime_squares(limit=50):
    count = 0
    prime = 2
    reversible_prime_squares = []
    
    while count < limit:
        if isprime(prime):
            prime_square = prime**2
            reversed_square = reverse_number(prime_square)
            
            if isprime(int(np.sqrt(reversed_square))) and int(np.sqrt(reversed_square))**2 == reversed_square:
                if not is_palindrome(prime_square):
                    reversible_prime_squares.append(prime_square)
                    count += 1
        prime += 1
    
    return sum(reversible_prime_squares)

# Finding the sum of the first 50 reversible prime squares
sum_reversible_prime_squares = find_reversible_prime_squares()
print(sum_reversible_prime_squares)
