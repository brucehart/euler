#Author: Bruce Hart <bruce.hart@gmail.com>

import time
import math
import random

def f(q,c):
    r = 1

    for a in xrange(1,51):
        if (c[a-1] > 0):
            r *= (1-(a/q))
        else:
            r *= (a/q)

        print r

    r*=math.factorial(50)
    r/=math.factorial(30)
    r/=math.factorial(20)

    r = r-0.2
    print r
    return r

def secantSolve(n,n0,n1,c):
    r = 0

    for i in xrange(0,n):
        if (f(n1,c) == f(n0,c)): return r
        r = n1 - f(n1,c)*((n1 - n0)/(f(n1,c)-f(n0,c)))
        n0 = n1
        n1 = r

    return r

def genC(p,d):
    c = [0]*p

    for x in random.sample(xrange(0,p),d):
        c[x] = 1
    return c


def euler286():
    q = []
    for j in xrange(0,100):
        c = genC(50,20)
        secantSolve(100,51.0,52.0,c)

if __name__ == '__main__':
    time.clock()
    euler286()
    print "Executed in {0} sec".format(time.clock())