# Author: Bruce Hart <bruce.hart@gmail.com>

# Let r be the remainder when (a-1)^n + (a+1)^n is divided by a^2.
#
# For example, if a = 7 and n = 3, then r = 42: 63 + 83 = 728 = 42 mod 49. And as n varies,
# so too will r, but for a = 7 it turns out that r_max = 42.
#
# For 3 <= a <= 1000, find sum(rmax).

def r_max(a):
    # When n is even, r = 2 for all cases
    # When n is odd, r = 2 * a * n
    # Maximum r is when n is odd and equals (a - 1) // 2
    return max([2,2*a*int((a-1)//2)])

def euler120():
    print(sum(r_max(a) for a in range(3, 1001)))

if __name__ == '__main__':
    euler120()
