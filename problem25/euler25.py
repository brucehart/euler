#Author: Bruce Hart <bruce.hart@gmail.com>

#The Fibonacci sequence is defined by the recurrence relation:
#
#Fn = Fn-1 + Fn-2, where F1 = 1 and F2 = 1.
#
#Hence the first 12 terms will be:
#
#F1 = 1
#F2 = 1
#F3 = 2
#F4 = 3
#F5 = 5
#F6 = 8
#F7 = 13
#F8 = 21
#F9 = 34
#F10 = 55
#F11 = 89
#F12 = 144
#
#The 12th term, F12, is the first term to contain three digits.
#
#What is the first term in the Fibonacci sequence to contain 1000 digits?

import time

#Fibonacci sequence generator
def fib():
    yield 1
    yield 1

    n_1 = 1
    n_2 = 1

    while True:
        n = n_1 + n_2
        yield n
        n_2 = n_1
        n_1 = n


def euler25():
    f = fib()

    c = 1

    while f.next() < (10**999):
        c += 1

    print c

if __name__ == '__main__':
    time.clock()
    euler25()
    print "Executed in {0} sec".format(time.clock())