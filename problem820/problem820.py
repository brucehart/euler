import math 

def d(n, k):
    return (10*pow(10,n-1,k))//k

def S(n):
    return sum([d(n, k) for k in range(1, n + 1)])

print(S(10**7))
