#Author: Bruce Hart <bruce.hart@gmail.com>

#Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
#
#21 22 23 24 25
#20  7  8  9 10
#19  6  1  2 11
#18  5  4  3 12
#17 16 15 14 13
#
#It can be verified that the sum of the numbers on the diagonals is 101.
#
#What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?


import time

def spiralDiags(N):
    r = 1
    c = 0
    p = 1

    yield r

    while True:
        #corner numbers for each sub-square (diagonals) increase in steps of 2*p,
        # p increases after each set of four corners
        r += 2*p
        c += 1

        if r > N**2: break
        yield r

        if c == 4:
            c = 0
            p += 1


def euler28():
    N = 1001
    print sum(spiralDiags(N))

if __name__ == '__main__':
    time.clock()
    euler28()
    print "Executed in {0} sec".format(time.clock())