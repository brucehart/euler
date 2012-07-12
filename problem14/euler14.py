#Author: Bruce Hart <bruce.hart@gmail.com>

#The following iterative sequence is defined for the set of positive integers:
#
#n -> n/2 (n is even)
#n -> 3n + 1 (n is odd)
#
#Using the rule above and starting with 13, we generate the following sequence:
#13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
#
#It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been
# proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
#
#Which starting number, under one million, produces the longest chain?
#
#NOTE: Once the chain starts the terms are allowed to go above one million.

import time

def nextChain(i):
    if (i%2 == 0):
        return i//2
    else:
        return 3*i+1

def getSequenceLength(v,N,chain_lengths):
    count = 0
    while v > 1:
        count += 1
        v = nextChain(v)
        #store chain lengths to avoid repeating a sequence once a length has been computed
        #need to check if v < N to avoid out-of-bounds error (v exceeds N in some sequences)
        if v < N and chain_lengths[v] > 0:
            return count + chain_lengths[v]
    return count

def euler14():
    N = 1000000
    chain_lengths = [0]*N
    long_chain = 0
    long_chain_start = 0

    for m in xrange(13,N):
        c = getSequenceLength(m,N,chain_lengths)
        chain_lengths[m] = c
        if c > long_chain :
            long_chain = c
            long_chain_start = m

    print long_chain_start

if __name__ == '__main__':
    time.clock()
    euler14()
    print "Executed in {} sec".format(time.clock())