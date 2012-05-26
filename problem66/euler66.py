#Author: Bruce Hart <bruce.hart@gmail.com>

#Consider quadratic Diophantine equations of the form:
#
#x2 – Dy2 = 1
#
#For example, when D=13, the minimal solution in x is 6492 – 13×1802 = 1.
#
#It can be assumed that there are no solutions in positive integers when D is square.
#
#By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
#
#32 – 2×22 = 1
#22 – 3×12 = 1
#92 – 5×42 = 1
#52 – 6×22 = 1
#82 – 7×32 = 1
#
#Hence, by considering minimal solutions in x for D = 7, the largest x is obtained when D=5.
#
#Find the value of D = 1000 in minimal solutions of x for which the largest value of x is obtained.


def findMinX(D):
    #print D
    y = 1.0
    while True:
        x = (1+D*y*y)**0.5

        if x%1 == 0:
            return int(x)
        y+=1.0

    return 0

D_MAX = 1000

d = range(D_MAX+1)
#only use cases where D is not square per instructions
d = filter(lambda z: (z**0.5)%1 != 0,d)
min_x = map(findMinX,d)
largest_x = max(min_x)
#find the D value that corresponds to the first matching max in min_x
largest_d = d[min_x.index(largest_x)]

#print both values, second one is the required output
print largest_x
print largest_d

