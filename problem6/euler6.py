#Author: Bruce Hart <bruce.hart@gmail.com>

#The sum of the squares of the first ten natural numbers is,
#1^2 + 2^2 + ... + 10^2 = 385
#
#The square of the sum of the first ten natural numbers is,
#(1 + 2 + ... + 10)^2 = 55^2 = 3025
#
#Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.
#
#Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

import time

def euler6():
    D = 100

    n = xrange(1,D+1)

    sum_squares = reduce(lambda x,y: x+y**2,n)
    square_sum = sum(n)**2

    diff = square_sum - sum_squares

    print diff

if __name__ == '__main__':
    time.clock()
    euler6()
    print "Executed in {} sec".format(time.clock())