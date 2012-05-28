#Author: Bruce Hart <bruce.hart@gmail.com>

#In the 20*20 grid below, four numbers along a diagonal line have been marked in red.
# ...[see problem11_data.txt]
#The product of these numbers is 26 * 63 * 78 * 14 = 1788696
#
#What is the greatest product of four adjacent numbers in any direction (up, down, left, right, or diagonally) in the 20*20 grid?

import time

def findLRProduct(data,idx):
    return reduce(lambda x,y: x*y,data[idx:idx+4])

def findDownProduct(data,idx,w):
    return reduce(lambda x,y: x*y,data[idx:idx+4*w:w])

def findDiagDownProduct(data,idx,w):
    return reduce(lambda x,y: x*y,data[idx:idx+4*w+4:w+1])

def findDiagUpProduct(data,idx,w):
    return reduce(lambda x,y: x*y,data[idx:idx+4*(w-1):w-1])

def euler11():
    N = 400
    W = int(N**0.5)
    idx_n = range(400)
    max_product = []

    f = open('problem11_data.txt')
    data = []
    map(lambda x: data.extend(x.replace('\n','').split(' ')),f.readlines())
    data = map(lambda x: int(x),data)

    max_product.append(max(map(lambda z: findLRProduct(data,z),filter(lambda x: x%W <= (W-4),idx_n))))
    max_product.append(max(map(lambda z: findDownProduct(data,z,W),filter(lambda x: x//W <= (W-4),idx_n))))
    max_product.append(max(map(lambda z: findDiagDownProduct(data,z,W),filter(lambda x: x%W <= (W-4) and x//W <= (W-4),idx_n))))
    max_product.append(max(map(lambda z: findDiagUpProduct(data,z,W),filter(lambda x: x%W >= 3 and x//W <= (W-4),idx_n))))

    print max(max_product)

if __name__ == '__main__':
    time.clock()
    euler11()
    print "Executed in {} sec".format(time.clock())