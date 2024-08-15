# Author: Bruce Hart
# Email: bruce.hart@gmail.com

# This script calculates the last ten digits of the series 1^1 + 2^2 + 3^3 + ... + 1000^1000.
# It demonstrates the use of large numbers and modular arithmetic to manage potentially large calculations.

def euler48():
    """ Calculate the last ten digits of the series 1^1 + 2^2 + 3^3 + ... + 1000^1000 """
    total = sum(x**x for x in range(1, 1001))
    print(total % (10**10))

if __name__ == '__main__':
    euler48()
