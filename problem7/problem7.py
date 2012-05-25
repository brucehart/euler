#Author: Bruce Hart <bruce.hart@gmail.com>

#By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
#
#What is the 10001st prime number?

def isprime(x):
    for n in range(2,int(x**0.5)+1):
        if (x%n == 0 and x != n):
            return False
    return True

def infiniteCount():
    c = 1
    while True:
        c +=1
        yield c

P = 10001

count = 0

for n in infiniteCount():
    if (isprime(n)): count += 1
    if count == P : break

print n


