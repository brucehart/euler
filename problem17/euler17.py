#Author: Bruce Hart <bruce.hart@gmail.com>

#If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

#If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

#NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115
# (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.

import time

def numberToPhrase(n):
    letterCounts = [4, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8, 6, 6, 5, 5, 5, 7, 6, 6, 7, 8]

    if (n <= 20):
        return letterCounts[n]
    elif (n < 100):
        if (n % 10 == 0):
            return letterCounts[(n-20)//10+20]
        else:
            return letterCounts[(n-20)//10+20] + letterCounts[n%10]
    elif (n<1000):
        #letterCounts[29] --> len("hundred")
        if (n % 100 == 0):
            return letterCounts[n//100] + letterCounts[28]
        else:
            return letterCounts[n//100] + letterCounts[28] + 3 + numberToPhrase(n%100)
    elif (n < 10000):
        #letterCounts[29] --> len("thousand")
        if (n % 1000 == 0):
            return letterCounts[n//1000] + letterCounts[29]
        else:
            return letterCounts[n//1000] + letterCounts[29] + numberToPhrase(n%1000)
    else:
        return 0


def euler17():
    #for i in range(1,1001):
    #    print str(i) + ":" + str(numberToPhrase(i))

    N = 1000
    D = xrange(1,N+1)
    print sum(map(numberToPhrase,D))

if __name__ == '__main__':
    time.clock()
    euler17()
    print "Executed in {0} sec".format(time.clock())