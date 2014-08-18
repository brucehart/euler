# -*- coding: utf-8 -*-
#Author: Bruce Hart <bruce.hart@gmail.com>

#The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330,
# is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the
# 4-digit numbers are permutations of one another.
#
#There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property,
# but there is one other 4-digit increasing sequence.
#
#What 12-digit number do you form by concatenating the three terms in this sequence?

import time
import itertools

def build_prime_list(N):
    p = 2
    last_p = p
    prime_list = [1]*N

    prime_list[0] = 0

    while last_p < N:
        p = 2*last_p

        while p <= N:
            prime_list[p-1] = 0
            p = p + last_p

        last_p = last_p + 1

        while (last_p <= N) and (prime_list[last_p-1] == 0):
            last_p = last_p + 1

    return prime_list


def is_permutation(a,b):
    if (a != b and sorted(list(str(a))) == sorted(list(str(b)))):
        return True
    else:
        return False

def euler49():
    primes = build_prime_list(10**4+1)
    results = []
    skips = []

    for i in range(1000, 9999):

        if (i in skips):
            continue

        p = filter(lambda x: is_permutation(i,x), range(1000,9999))

        map(skips.append, p)

        p = filter(lambda x: (primes[x-1] == 1), p)

        #find sets with at least 3 entries to evaluate
        #and skip the example set given in the problem
        if (len(p) >= 3) and (1487 not in p):
            p = sorted(p)

            for j in range(0, len(p)-1):
                for k in range(j+1, len(p)):
                    if (2*p[k] - p[j]) in p:
                        print (p[j], p[k], 2*p[k] - p[j])


if __name__ == '__main__':
    time.clock()
    euler49()
    print "Executed in {0} sec".format(time.clock())