# -*- coding: utf-8 -*-
# Author: Bruce Hart <bruce.hart@gmail.com>

# In England the currency is made up of pound, �, and pence, p, and there are eight coins in general circulation:
#
# 1p, 2p, 5p, 10p, 20p, 50p, �1 (100p) and �2 (200p).
# It is possible to make �2 in the following way:
#
# 1x�1 + 1x50p + 2x20p + 1x5p + 1x2p + 3x1p
# How many different ways can �2 be made using any number of coins?

# Recursive function that returns the number of ways a set of coins can be used to form a value
def combos(vals, idx, tot):
    # If previous value and total are equal, return 1 (match)
    if tot == 0:
        return 1
    # If we traverse beyond the total or number of coins, return 0 (no match)
    elif tot < 0 or idx <= 0:
        return 0
    else:
        # Recursively add up all of the combinations
        return combos(vals, idx-1, tot) + combos(vals, idx, tot-vals[idx-1])

def euler31():
    total = 200
    coins = [1, 2, 5, 10, 20, 50, 100, 200]

    print(combos(coins, len(coins), total))

if __name__ == '__main__':
    euler31()

