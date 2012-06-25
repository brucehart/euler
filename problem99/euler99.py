#Author: Bruce Hart <bruce.hart@gmail.com>

#Comparing two numbers written in index form like 2^11 and 3^7 is not difficult,
# as any calculator would confirm that 2^11 = 2048 < 3^7 = 2187.
#
#However, confirming that 632382^518061 > 519432^525806
# would be much more difficult, as both numbers contain over three million digits.
#
#Using base_exp.txt (right click and 'Save Link/Target As...'), a 22K text file containing one thousand lines
# with a base/exponent pair on each line, determine which line number has the greatest numerical value.
#
#NOTE: The first two lines in the file represent the numbers in the example given above.


import time
import math

def euler99():
    max_log = 0
    max_line = 0
    n = 1
    f = open('base_exp.txt')

    for line in f:
        vals = line.strip().split(",")
        v = math.log(int(vals[0]))*int(vals[1])
        if v > max_log:
            max_log = v
            max_line = n
        n += 1

    print max_line


if __name__ == '__main__':
    time.clock()
    euler99()
    print "Executed in {0} sec".format(time.clock())

