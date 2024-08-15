# -*- coding: utf-8 -*-
# Author: Bruce Hart
# Email: bruce.hart@gmail.com

# This script finds unusual arithmetic sequences of three 4-digit primes,
# where each term is a permutation of the others and the sequence has a constant difference.
# The aim is to identify another sequence other than the known 1487, 4817, 8147, and concatenate them.

import itertools

def build_prime_list(N):
    """ Generate a list indicating prime status for numbers up to N. """
    prime_list = [True] * N
    prime_list[0] = prime_list[1] = False

    for start in range(2, int(N**0.5) + 1):
        if prime_list[start]:
            for i in range(start*start, N, start):
                prime_list[i] = False

    return prime_list

def is_permutation(a, b):
    """ Check if two numbers are permutations of each other. """
    return sorted(str(a)) == sorted(str(b))

def euler49():
    """ Search for all 4-digit arithmetic sequences of primes that are permutations of each other. """
    primes = build_prime_list(10000)
    results = []
    skips = set()

    for i in range(1000, 10000):
        if i in skips:
            continue

        # Generate permutations that are also primes
        permutations = [x for x in range(1000, 10000) if is_permutation(i, x) and primes[x]]
        skips.update(permutations)

        # Check the specific condition excluding the known sequence
        if len(permutations) >= 3 and 1487 not in permutations:
            permutations.sort()
            for j in range(len(permutations)):
                for k in range(j + 1, len(permutations)):
                    diff = permutations[k] - permutations[j]
                    if permutations[k] + diff in permutations:
                        results.append((permutations[j], permutations[k], permutations[k] + diff))

    # Print results excluding the initial example
    for result in results:
        if 1487 not in result:
            print("".join(str(x) for x in result))
            break

if __name__ == '__main__':
    euler49()

