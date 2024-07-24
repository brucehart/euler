from itertools import combinations

def sieve_of_eratosthenes(limit):
    sieve = [True] * limit
    sieve[0] = sieve[1] = False
    for start in range(2, int(limit**0.5) + 1):
        if sieve[start]:
            for multiple in range(start*start, limit, start):
                sieve[multiple] = False
    return [num for num, is_prime in enumerate(sieve) if is_prime]

def generate_patterns(number):
    str_num = str(number)
    length = len(str_num)
    patterns = []
    for num_replacements in range(1, length):
        for digits in combinations(range(length), num_replacements):
            pattern = list(str_num)
            for digit in digits:
                pattern[digit] = '*'
            patterns.append(''.join(pattern))
    return patterns

def find_prime_family(limit, family_size):
    primes = set(sieve_of_eratosthenes(limit))
    for prime in primes:
        patterns = generate_patterns(prime)
        for pattern in patterns:
            family = []
            for digit in '0123456789':
                candidate = int(pattern.replace('*', digit))
                if candidate in primes and len(str(candidate)) == len(pattern):
                    family.append(candidate)
            if len(family) == family_size:
                return min(family)
    return None

# Set a limit for the prime numbers (can be adjusted)
limit = 1000000
family_size = 8

result = find_prime_family(limit, family_size)
print(f"The smallest prime which is part of an {family_size} prime value family is: {result}")
