#Author: Bruce Hart <bruce.hart@gmail.com>

#A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
#a^2 + b^2 = c^2
#
#For example, 3^2 + 4^2 = 9 + 16 = 25 = 52.
#
#There exists exactly one Pythagorean triplet for which a + b + c = 1000.
#Find the product abc.

import time
import itertools

def isPythag(a,b,c):
    return (a**2 + b**2) == c**2;

def euler9():
    D = 1000
    N = xrange(1,D+1)

    #find combinations for a and b
    comb = itertools.combinations_with_replacement(N,2)
    #filter out sets that don't match the criteria
    result = filter(lambda x:(x[0]+x[1] < D) and isPythag(x[0],x[1],D-x[0]-x[1]),comb)
    #append c (= D-a-b) to each result
    result = map(lambda x: [x[0],x[1],D-x[0]-x[1]],result)
    #print result

    #compute the product a*b*c
    ans = map(lambda x: x[0]*x[1]*x[2],result)
    print ans[0]

if __name__ == '__main__':
    time.clock()
    euler9()
    print "Executed in {} sec".format(time.clock())

