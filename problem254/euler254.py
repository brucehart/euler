#Author: Bruce Hart <bruce.hart@gmail.com>

#Define f(n) as the sum of the factorials of the digits of n. For example, f(342) = 3! + 4! + 2! = 32.
#
#Define sf(n) as the sum of the digits of f(n). So sf(342) = 3 + 2 = 5.
#
#Define g(i) to be the smallest positive integer n such that sf(n) = i. Though sf(342) is 5, sf(25) is also 5, and it can be verified that g(5) is 25.
#
#Define sg(i) as the sum of the digits of g(i). So sg(5) = 2 + 5 = 7.
#
#Further, it can be verified that g(20) is 267 and sum(sg(i)) for 1 <= i <= 20 is 156.
#
#What is sum(sg(i)) for 1 <= i <= 150?

import time
import math
import itertools

def f(x):
    sv = map(lambda x: math.factorial(int(x)),str(x))
    return sum(sv)

def sf(x):
    return sum(map(lambda x: int(x),str(f(x))))

def min_seq(vals):
    ret_seq = ""

    for n in range(1,10):
        if vals[n] > 0:
            ret_seq = str(n)
            vals[n] = vals[n] - 1
            break

    for n in range(0,10):
        while vals[n] > 0:
            ret_seq = ret_seq + str(n)
            vals[n] = vals[n] - 1

    return ret_seq

def reduced_seq(val,fact_vals):
    ret_reduced = [0]*10


    for i in range(9,-1,-1):
        while (val > 0 and val >= fact_vals[i]):
            ret_reduced[i] += 1
            val = val - fact_vals[i]

        if ret_reduced[1] > 1:
            ret_reduced[0] = ret_reduced[1]-1
            ret_reduced[1] = 1

    return ret_reduced

def euler254():
    g = [0]*151

    fact_vals = [1,1,2,6,24,120,720,5040,40320,362880]


    for i in range(1,10**5):
    #for seq in itertools.product(range(3),repeat=10):
        #seq_sum = sum(map(lambda x,y: x*y,seq,range(10)))
        seq_sum = i
        seq = reduced_seq(i,range(10))
        digit_sum = reduce(lambda x,y: int(x)+int(y),str(seq_sum))

        if seq_sum == 20:
            print seq


        sg = min_seq(reduced_seq(seq_sum,fact_vals))

        if digit_sum <= 150 and (g[digit_sum] == 0 or g[digit_sum] > sg):
            g[digit_sum] = sg

    print g

if __name__ == '__main__':
    time.clock()
    euler254()
    print "Executed in {0} sec".format(time.clock())
