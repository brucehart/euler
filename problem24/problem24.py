#Author: Bruce Hart <bruce.hart@gmail.com>

#A permutation is an ordered arrangement of objects. For example, 3124 is one possible
#permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or
#alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2
#are:
#
#012   021   102   120   201   210
#
#What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

import math
import time

def euler24():
    numbers = [0,1,2,3,4,5,6,7,8,9]
    target = 10**6-1
    result = 0

    while (len(numbers) > 0):
        idx = int(math.floor(target / math.factorial(len(numbers)-1)))
        result *= 10
        result += numbers[idx]
        target -= idx*math.factorial(len(numbers)-1)
        del numbers[idx]

    print(result)

if __name__ == '__main__':
    time.clock()
    euler24()
    print "Executed in {} sec".format(time.clock())