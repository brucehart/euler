#Author: Bruce Hart <bruce.hart@gmail.com>

#The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, is a ninth power.
#
#How many n-digit positive integers exist which are also an nth power?

import time
import math

def euler63():
    #to meet the criteria, b^n > 10^(n-1) and b^n < 10^n
    #using the natrual log, we can find this means b < 10 and b > exp(ln(10)*(n-1)/n)
    #if  exp(ln(10)*(n-1)/n) > 10, then no solutions exist for this n or any greater n
    #to count matching values of b,for a given n, we round up  exp(ln(10)*(n-1)/n) to the nearest integer
    #and then count integers that are greater than or equal to that value and less than 10
    count = 0
    
    n = 1
    
    while True:
        c = math.ceil(math.exp(math.log(10)*(n-1)/n))
        if c >= 10:
            break
        else:
            count += int(10-c)
            
        n +=1
        
    print count
        

if __name__ == '__main__':
    time.clock()
    euler63()
    print "Executed in {0} sec".format(time.clock())