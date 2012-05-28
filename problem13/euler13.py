#Author: Bruce Hart <bruce.hart@gmail.com>

#Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
# (see problem13_d.txt)

import time

def sumCol(r,carry):
    s = sum(r) + carry
    return [s//10,s%10]

def euler13():
    d = open('problem13_data.txt').readlines()
    d = map(lambda x: list(x.strip()),d)
    d = map(lambda x: map(lambda y: int(y),x),d)

    N = 50
    strSum = ''
    carry = 0
    sumResult = 0

    for k in xrange(N):
        r = map(lambda x: x[-k-1],d)
        [carry,sumResult] = sumCol(r,carry)
        strSum = str(sumResult) + strSum

    strSum = str(carry) + strSum
    print strSum[0:10]

if __name__ == '__main__':
    time.clock()
    euler13()
    print "Executed in {} sec".format(time.clock())

