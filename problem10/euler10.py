#Author: Bruce Hart <bruce.hart@gmail.com>

#The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
#
#Find the sum of all the primes below two million.

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

def euler10():
    D = 2000000
    #D = 2000
    N = xrange(1,D+1)
    prime_list = build_prime_list(D)
    p = filter(lambda x: isprime(x, prime_list),N)
    s = sum(p)

    print s

if __name__ == '__main__':
    time.clock()
    euler10()
    print "Executed in {} sec".format(time.clock())