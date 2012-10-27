#Author: Bruce Hart <bruce.hart@gmail.com>

#Build a triangle from all positive integers in the following way:
#
#1
#2  3
#4  5  6
#7  8  9 10
#11 12 13 14 15
#16 17 18 19 20 21
#22 23 24 25 26 27 28
#29 30 31 32 33 34 35 36
#37 38 39 40 41 42 43 44 45
#46 47 48 49 50 51 52 53 54 55
#56 57 58 59 60 61 62 63 64 65 66
#. . .
#
#Each positive integer has up to eight neighbours in the triangle.
#
#A set of three primes is called a prime triplet if one of the three primes has the other two as neighbours in the triangle.
#
#For example, in the second row, the prime numbers 2 and 3 are elements of some prime triplet.
#
#If row 8 is considered, it contains two primes which are elements of some prime triplet, i.e. 29 and 31.
#If row 9 is considered, it contains only one prime which is an element of some prime triplet: 37.
#
#Define S(n) as the sum of the primes in row n which are elements of any prime triplet.
#Then S(8)=60 and S(9)=37.
#
#You are given that S(10000)=950007619.
#
#Find  S(5678027) + S(7208785).

import time

def isprime(x):
    if (x<=1): return False

    for n in range(2,int(x**0.5)+1):
        if (x%n == 0 and x != n):
            return False
    return True

def computeS(n):
    row = getRow(n)
    primes = filter(isprime,row)
    print primes

def getRow(n):
    rowStart = (n-1)*n/2 + 1
    return range(rowStart,rowStart+n)

def euler196():
    computeS(5678027)


if __name__ == '__main__':
    time.clock()
    euler196()
    print "Executed in {0} sec".format(time.clock())