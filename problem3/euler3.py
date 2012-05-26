#Author: Bruce Hart <bruce.hart@gmail.com>

#The prime factors of 13195 are 5, 7, 13 and 29.
#
#What is the largest prime factor of the number 600851475143 ?

def isprime(x):
    for n in range(2,int(x**0.5)+1):
        if (x%n == 0 and x != n):
            return False
    return True


D = 600851475143

factors = range(2,int(D**0.5)+1)
factors = filter(lambda x: D%x==0,factors)
factors = filter(isprime,factors)


print max(factors)

