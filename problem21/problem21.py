#Author: Bruce Hart <bruce.hart@gmail.com>

#Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
#If d(a) = b and d(b) = a, where a != b, then a and b are an amicable pair and each of a and b
# are called amicable numbers.
#
#For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110;
# therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
#
#Evaluate the sum of all the amicable numbers under 10000.

import time


def getFactors(n):
    factors = set()
    for i in xrange(1,n/2+1):
        if n%i == 0:
            factors.add(i)

    return list(factors)

def d(n): return sum(getFactors(n))

def euler21():
    amb = set()

    for n in xrange(10000):
        r = d(n)
        if (n == d(r) and n != r):
            amb.add(n)
            amb.add(r)

    print sum(amb)

if __name__ == '__main__':
    time.clock()
    euler21()
    print "Executed in {0} sec".format(time.clock())