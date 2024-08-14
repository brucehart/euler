#Author: Bruce Hart <bruce.hart@gmail.com>

#There are exactly ten ways of selecting three from five, 12345:
#
#123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
#
#In combinatorics, we use the notation, 5C3 = 10.
#
#In general, nCr = n!/(r!(n-r)!)
#where r = n, n! = n*(n-1)*...*3*2*1, and 0! = 1.
#
#It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
#How many, not necessarily distinct, values of  nCr, for 1 = n = 100, are greater than one-million?


import time
import math

def nCr(n,r):
    return math.factorial(n)/(math.factorial(r)*math.factorial(n-r))
    
def nCrCount(n,lim):
    return len(filter(lambda x: x>lim,map(lambda r: nCr(n,r),xrange(1,n+1))))
    
def euler53():
    print sum(map(lambda x: nCrCount(x,10**6),xrange(1,101)))
    

if __name__ == '__main__':
    time.clock()
    euler53()
    print "Executed in {0} sec".format(time.clock())