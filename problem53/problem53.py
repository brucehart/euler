# Author: Bruce Hart
# Email: bruce.hart@gmail.com

# The code calculates the number of combinations nCr that exceed one million for 1 <= n <= 100.
# nCr represents the number of ways to choose r elements from a set of n elements, calculated as n! / (r! * (n-r)!).
# The challenge is to find how many combinations exceed one-million across different values of n.

import math

def nCr(n, r):
    """ Calculate the binomial coefficient nCr = n! / (r! * (n-r)!) """
    return math.factorial(n) // (math.factorial(r) * math.factorial(n - r))
    
def nCrCount(n, lim):
    """ Count how many values of nCr for a given n are greater than lim """
    return sum(1 for r in range(1, n + 1) if nCr(n, r) > lim)
    
def euler53():
    """ Calculate the number of combinations greater than one million for 1 <= n <= 100 """
    print(sum(nCrCount(n, 10**6) for n in range(1, 101)))

if __name__ == '__main__':
    euler53()

