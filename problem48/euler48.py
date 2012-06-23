#Author: Bruce Hart <bruce.hart@gmail.com>

#The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
#Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

import time

def euler48():
    val = sum(map(lambda x: x**x,xrange(1,1001)))
    print val%(10**10)
    

if __name__ == '__main__':
    time.clock()
    euler48()
    print "Executed in {0} sec".format(time.clock())