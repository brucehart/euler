# -*- coding: utf-8 -*-
#Author: Bruce Hart <bruce.hart@gmail.com>

# A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
# For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

# A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

# As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. 
# By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

# Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.


import time

def build_prime_list(N):
    p = 2
    last_p = p
    prime_list = [1]*N

    prime_list[0] = 0

    while last_p < N:
        p = 2*last_p

        while p <= N:
            prime_list[p-1] = 0
            p = p + last_p

        last_p = last_p + 1

        while (last_p <= N) and (prime_list[last_p-1] == 0):
            last_p = last_p + 1

    return prime_list

def isprime(x, prime_list = None):
    if (x<=1): return False

    if (prime_list == None):
        for n in range(2,int(x**0.5)+1):
            if (x%n == 0 and x != n):
                return False
        return True
    else:
        if (prime_list[x - 1] == 0):
            return False
        else:
            return True

def get_divisor_sum(prime_list, N):
    sum = 1

    for i in range(2, (N/2)+1):
        if isprime(i, prime_list) and (N%i) == 0:
            sum += i

    return sum 
    

def abundant_number(prime_list, N):
    s = get_divisor_sum(prime_list, N)

    if s < N:
        return -1
    elif s == N:
        return 0
    else:
        return 1

def abundant_number_list(N):
    abd_num = set()
    prime_list = build_prime_list(N)

    for i in xrange(1,N+1):
        if abundant_number(prime_list, i) > 0:
            abd_num.add(i)

    return abd_num

def is_abd_sum(abd_num, N):
    for i in abd_num:
        if (N-i) in abd_num:
            return True

    return False


def euler23():
    TEST_MAX = 28123
    
    abd_num = abundant_number_list(TEST_MAX)
    
    sum_total = 0

    print len(abd_num)

    # for i in xrange(24,TEST_MAX+1):
    #     if is_abd_sum(abd_num, i):
    #         sum_total += i

    # print sum_total




if __name__ == '__main__':
    time.clock()
    euler23()
    print "Executed in {0} sec".format(time.clock())