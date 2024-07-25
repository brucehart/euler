import math
from sympy import primerange, primepi, nextprime

def bsearch_le(left, right, callback):
    while left <= right:
        mid = (left + right) // 2
        cmp = callback(mid)
        if cmp == 0:
            return mid
        elif cmp < 0:
            left = mid + 1
        else:
            right = mid - 1
    return right

def count_hybrid_integers(n, e):
    limit = math.log(n) * e
    count = 0

    p = 2
    while True:
        p_log = math.log(p)
        upper_bound = int(limit / p_log)

        k = bsearch_le(p + 1, upper_bound, lambda q: p_log * q + math.log(q) * p - limit)

        if k <= p:
            break

        count += primepi(k) - primepi(p)
        p = nextprime(p)

    return count

# Given number for the problem
n = 800800
e = 800800

# Calculate the number of hybrid integers less than or equal to n
result = count_hybrid_integers(n, e)

print(result)
