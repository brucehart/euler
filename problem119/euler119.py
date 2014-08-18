# -*- coding: utf-8 -*-
#Author: Bruce Hart <bruce.hart@gmail.com>

#The number 512 is interesting because it is equal to the sum of its digits raised to some power:
# 5 + 1 + 2 = 8, and 8^3 = 512. Another example of a number with this property is 614656 = 28^4.
#
#We shall define an to be the nth term of this sequence and insist that a number must contain at least
# two digits to have a sum.
#
#You are given that a_2 = 512 and a_10 = 614656.
#
#Find a_30.

import time
import math

def digit_sum(n):
    return sum(map(lambda x: int(x), list(str(n))))


def euler119():
    a = []

    #Tried searching forward at first : look at sequential numbers, find those that have the property
    # ln(x)/ln(sum_of_digits) == integer -- found solutions, but takes a very long term beyond the first few matches
    #
    #This method searches backwards: finds solutions in the form of x**y and then determines if the base value equals
    # the sum of the digits in the exponential results. This method works quickly, but yields very large values
    # (including the solution!)
    for i in range(2, 501):
        for j in range(2, 51):
            v = i**j

            if (digit_sum(v) == i):
                a.append(v)

    a = sorted(a)

    if (len(a) >= 30):
        print a[29]

if __name__ == '__main__':
    time.clock()
    euler119()
    print "Executed in {0} sec".format(time.clock())