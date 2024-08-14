# -*- coding: utf-8 -*-
# Author: Bruce Hart <bruce.hart@gmail.com>

# The number 512 is interesting because it is equal to the sum of its digits raised to some power:
# 5 + 1 + 2 = 8, and 8^3 = 512. Another example of a number with this property is 614656 = 28^4.
#
# We shall define an to be the nth term of this sequence and insist that a number must contain at least
# two digits to have a sum.
#
# You are given that a_2 = 512 and a_10 = 614656.
#
# Find a_30.

def digit_sum(n):
    """Calculate the sum of the digits of a number."""
    return sum(int(x) for x in str(n))

def euler119():
    a = []

    # Instead of searching forwards, this method generates powers of numbers and checks if the sum of digits
    # of these numbers raised to a power equals the base of the power. This method works quickly and efficiently.
    for i in range(2, 501):
        for j in range(2, 51):
            v = i ** j
            if digit_sum(v) == i:
                a.append(v)

    a = sorted(a)

    if len(a) >= 30:
        print(a[29])

if __name__ == '__main__':
    euler119()
