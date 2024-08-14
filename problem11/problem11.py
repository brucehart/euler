# Author: Bruce Hart <bruce.hart@gmail.com>

# In the 20x20 grid below, four numbers along a diagonal line have been marked in red.
# ...[see problem11_data.txt]
# The product of these numbers is 26 * 63 * 78 * 14 = 1788696
# What is the greatest product of four adjacent numbers in any direction (up, down, left, right, or diagonally) in the 20x20 grid?

from functools import reduce
from operator import mul

def find_lr_product(data, idx):
    return reduce(mul, data[idx:idx+4])

def find_down_product(data, idx, w):
    return reduce(mul, data[idx:idx+4*w:w])

def find_diag_down_product(data, idx, w):
    return reduce(mul, data[idx:idx+4*w+4:w+1])

def find_diag_up_product(data, idx, w):
    return reduce(mul, data[idx:idx+4*(w-1):w-1])

def euler11():
    N = 400
    W = int(N**0.5)
    max_product = []

    with open('problem11_data.txt', 'r') as f:
        data = [int(x) for x in f.read().split()]

    # Horizontal products
    max_product.extend(find_lr_product(data, z) for z in range(N) if z % W <= W-4)
    
    # Vertical products
    max_product.extend(find_down_product(data, z, W) for z in range(N) if z // W <= W-4)
    
    # Diagonal down products
    max_product.extend(find_diag_down_product(data, z, W) for z in range(N) if z % W <= W-4 and z // W <= W-4)
    
    # Diagonal up products
    max_product.extend(find_diag_up_product(data, z, W) for z in range(N) if z % W >= 3 and z // W <= W-4)

    print(max(max_product))

if __name__ == '__main__':
    euler11()
