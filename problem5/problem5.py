#Author: Bruce Hart <bruce.hart@gmail.com>

#2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
#
#What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

import time
import itertools


def isDivisible(n,M):
    for m in range(2,M+1):
        if (n%m != 0):
            return False
    return True

def euler5():
    D = 20

    n = xrange(2,D+1)
    gMin = -1
    match = []

    #solution will be a combination of products from the range
    #loop through these combinations only rather than an exhaustive list for dramatic speed improvement
    for d in xrange(2,D+1):
        #use itertools to easily define all combinations
        #loop over xrange(2,D+1) to evaluate all combination list sizes
        comb = itertools.combinations(n,d)

        for c in comb:
            #take the rolling product, if it is divisible by all terms and less than our min so far, record it
            v = reduce(lambda x,y: x*y,c)
            if ((gMin < 0 or v < gMin) and isDivisible(v,D) > 0):
                gMin = v

    print gMin

if __name__ == '__main__':
    time.clock()
    euler5()
    print "Executed in {} sec".format(time.clock())