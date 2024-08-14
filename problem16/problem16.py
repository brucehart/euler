#Author: Bruce Hart <bruce.hart@gmail.com>

#2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
#What is the sum of the digits of the number 2^1000?

import time

def genDigits():
    seed = 2**1000
    
    while (seed > 0):
        r = seed%10
        seed //= 10
        yield r
    
def euler16():
    print sum(genDigits())

if __name__ == '__main__':
    time.clock()
    euler16()
    print "Executed in {0} sec".format(time.clock())