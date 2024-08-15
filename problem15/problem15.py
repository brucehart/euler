# Author: Bruce Hart <bruce.hart@gmail.com>

# The following iterative sequence is defined for the set of positive integers:
# Starting in the top left corner of a 2x2 grid, and only being able to move to the 
# right and down, there are exactly 6 routes to the bottom right corner.

# How many such routes are there through a 20x20 grid?

pC = dict()

# By deduction, we can find that the number of routes to x,y
#  1 route if x or y = 0
#  sum of computeRoutes(x-1, y) and computeRoutes(x, y-1) otherwise
#  cache the results in pC to limit the amount of recursion
def computeRoutes(x, y):
    if y > x:
        return computeRoutes(y, x)

    key = (x, y)

    if key in pC:
        return pC[key]    

    if y == 0:
        pC[key] = 1
    elif y > 0:
        pC[key] = computeRoutes(x, y-1) + computeRoutes(x-1, y)
    else:
        return 0

    return pC[key]

def euler15():
    x = 20
    y = 20
    n = computeRoutes(x, y)
    print(n)

if __name__ == '__main__':
    euler15()

