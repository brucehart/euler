#Author: Bruce Hart <bruce.hart@gmail.com>

#Consider the triangle with sides sqrt(5), sqrt(65) and sqrt(68). It can be shown that this triangle has area 9.
#
#S(n) is the sum of the areas of all triangles with sides sqrt(1+b^2), sqrt(1+c^2) and sqrt(b^2+c^2) (for positive integers b and c ) that have an integral area not exceeding n.
#
#The example triangle has b=2 and c=8.
#
#S(10^6)=18018206.
#
#Find S(10^10).

import time

def triangleArea(a,b,c):
    #Heron's formula: A = sqrt(p*(p-a)*(p-b)*(p-c)) where p = (a+b+c)/2
    p = (a+b+c)/2
    return (p*(p-a)*(p-b)*(p-c))**0.5
    
def euler390():
    N = 10**6
    S = 0
    T = set()
    for b in xrange(1,int(N**0.5)+0):
        for c in xrange(b,int(N**0.5)+0):
            if (b**2+c**2)**0.5 not in T:
                A = triangleArea((1+b**2)**0.5,(1+c**2)**0.5,(b**2+c**2)**0.5)
                T.add((b**2+c**2)**0.5)
            if (A <= N): S+=A
            else: break
    
    print int(S)

if __name__ == '__main__':
    time.clock()
    euler390()
    print "Executed in {0} sec".format(time.clock())
