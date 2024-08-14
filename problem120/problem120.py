#Author: Bruce Hart <bruce.hart@gmail.com>

#Let r be the remainder when (a-1)^n + (a+1)^n is divided by a^2.
#
#For example, if a = 7 and n = 3, then r = 42: 63 + 83 = 728 = 42 mod 49. And as n varies,
# so too will r, but for a = 7 it turns out that r_max = 42.
#
#For 3 <= a <= 1000, find sum(rmax).

import time

def r_max(a):
    #when n is even r = 2 for all cases
    #when n is odd r = 2*a*n
    #max for odd case is when n = floor((a-1)/2) or r = 2*a*floor((a-1)/2) = a*(a-1)
    return max([2,2*a*int((a-1)/2)])

def euler120():
    print sum(map(r_max,xrange(3,1001)))

if __name__ == '__main__':
    time.clock()
    euler120()
    print "Executed in {0} sec".format(time.clock())
