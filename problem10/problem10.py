#Author: Bruce Hart <bruce.hart@gmail.com>

#The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
#
#Find the sum of all the primes below two million.

def isprime(x):
    if (x<=1): return False

    for n in range(2,int(x**0.5)+1):
        if (x%n == 0 and x != n):
            return False
    return True

D = 2000000
N = xrange(1,D+1)
p = filter(isprime,N)
s = sum(p)

print s