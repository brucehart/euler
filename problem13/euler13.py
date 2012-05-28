#Author: Bruce Hart <bruce.hart@gmail.com>

#Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
# (see problem13_data.txt)

def sumCol(c):
    s = sum(map(lambda x: int(x),c))
    return [s//10,s%10]

data = open('problem13_data.txt').readlines()
data = map(lambda x: x.strip(),data)

N = 50

for k in xrange(N):
    r = map(lambda x: x[-1],data)
    [carry,sum] = sumCol(r)
    print "{} {}".format(carry,sum)


