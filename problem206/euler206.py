# -*- coding: utf-8 -*-
#Author: Bruce Hart <bruce.hart@gmail.com>

# Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
# where each “_” is a single digit.

import time
import math

def correct_form(N):
    #this numeric method is a little faster than returning str(N)[::2] == "1234567890"
    i = 18
    j = 1

    if (N % 10 != 0): return False

    while (i > 1):
        if (N // (10**i))%10 == j:
            i -= 2
            j += 1
        else:
            return False

    return True



def euler206():
    SEARCH_LOW = int(math.sqrt(1020304050607080900))
    SEARCH_HIGH = int(math.sqrt(1929394959697989990))

    for i in xrange(SEARCH_LOW - SEARCH_LOW%10, SEARCH_HIGH+1, 10):
        if correct_form(i**2):
            print i
            break

    
if __name__ == '__main__':
    time.clock()
    euler206()
    print "Executed in {0} sec".format(time.clock())