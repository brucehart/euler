import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def count_fractions_between(lower_bound, upper_bound, max_denominator):
    count = 0
    for d in range(2, max_denominator + 1):
        for n in range(1, d):
            if gcd(n, d) == 1:
                fraction = n / d
                if lower_bound < fraction < upper_bound:
                    count += 1
    return count

# Given bounds and max denominator
lower_bound = 1/3
upper_bound = 1/2
max_denominator = 12000

# Count the fractions
fraction_count = count_fractions_between(lower_bound, upper_bound, max_denominator)
print(fraction_count)
