import itertools
from math import sqrt, isqrt

# Sieve of Eratosthenes to generate a list of prime numbers
def generate_primes(limit):
    sieve = [True] * (limit + 1)
    sieve[0] = sieve[1] = False
    for start in range(2, isqrt(limit) + 1):
        if sieve[start]:
            for multiple in range(start*start, limit + 1, start):
                sieve[multiple] = False
    return [num for num, is_prime in enumerate(sieve) if is_prime]

# Check if a number is prime
def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

# Check if concatenating two primes results in another prime
def is_prime_concatenation(prime1, prime2):
    concat1 = int(str(prime1) + str(prime2))
    concat2 = int(str(prime2) + str(prime1))
    return is_prime(concat1) and is_prime(concat2)

# Recursively find sets of primes with the concatenation property
def find_prime_sets(primes, set_size, current_set=[]):
    if len(current_set) == set_size:
        return current_set
    
    for prime in primes:
        if all(is_prime_concatenation(prime, p) for p in current_set):
            new_set = current_set + [prime]
            result = find_prime_sets(primes, set_size, new_set)
            if result:
                return result
    return None

# Main function to solve the problem
def solve_prime_pair_sets(limit, set_size):
    primes = generate_primes(limit)
    for start_prime in primes:
        result_set = find_prime_sets(primes, set_size, [start_prime])
        if result_set:
            return result_set, sum(result_set)
    return None, None

# Solve for the set of five primes
limit = 10000  # Adjust this limit if needed
set_size = 5
prime_set, prime_sum = solve_prime_pair_sets(limit, set_size)
print(f"The set of five primes is: {prime_set}")
print(f"The lowest sum of these primes is: {prime_sum}")
