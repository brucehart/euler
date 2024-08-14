# Author: Bruce Hart <bruce.hart@gmail.com>

# It turns out that 12 cm is the smallest length of wire that can be bent to form an integer sided right angle triangle
# in exactly one way, but there are many more examples.
#
# 12 cm: (3,4,5)
# 24 cm: (6,8,10)
# 30 cm: (5,12,13)
# 36 cm: (9,12,15)
# 40 cm: (8,15,17)
# 48 cm: (12,16,20)
#
# In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right angle triangle,
# and other lengths allow more than one solution to be found; for example, using 120 cm it is possible to form exactly
# three different integer sided right angle triangles.
#
# 120 cm: (30,40,50), (20,48,52), (24,45,51)
#
# Given that L is the length of the wire, for how many values of L <= 1,500,000 can exactly
# one integer sided right angle triangle be formed?

import math

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

def euler75():
    N = 1500000
    wires = {}

    for m in range(1, int(math.floor(N**0.5))):
        for n in range(1, m):
            # Euler's method for Pythagorean triplets: multiples of a = m^2 - n^2, b = 2*m*n, c = m^2 + n^2
            # for m > n where m, n are co-prime and (m-n) is odd
            if gcd(m, n) != 1 or (m - n) % 2 == 0:
                continue

            a = m**2 - n**2
            b = 2*m*n
            c = m**2 + n**2
            d = a + b + c

            while d < N:
                if d in wires:
                    wires[d] += 1
                else:
                    wires[d] = 1
                d += (a + b + c)

    wirecount = len([x for x in wires.values() if x == 1])
    print(wirecount)

if __name__ == '__main__':
    euler75()

