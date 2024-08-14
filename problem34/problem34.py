# -*- coding: utf-8 -*-
#Author: Bruce Hart <bruce.hart@gmail.com>

#145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
#
#Find the sum of all numbers which are equal to the sum of the factorial of their digits.
#
#Note: as 1! = 1 and 2! = 2 are not sums they are not included.

import time

fact = [0]*100

def initialize_factorials():
    fact[0] = 1

    for n in range(1, len(fact)):
        fact[n] = fact[n-1]*(n)

def factorial(x):
    return fact[x]

def factorial_sum(x):
    x = list(str(x))
    x = map(lambda n: factorial(int(n)), x)
    return sum(x)

def euler34():
    matches = []
    initialize_factorials()
    maxN = factorial(9)*7

    for i in range(3, maxN+1):
        if (factorial_sum(i) == i):
            matches.append(i)

    print sum(matches)

if __name__ == '__main__':
    time.clock()
    euler34()
    print "Executed in {0} sec".format(time.clock())