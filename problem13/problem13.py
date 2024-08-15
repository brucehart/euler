# Author: Bruce Hart <bruce.hart@gmail.com>

# Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
# (see problem13_d.txt)

def sumCol(r, carry):
    s = sum(r) + carry
    return [s // 10, s % 10]

def euler13():
    with open('problem13_data.txt') as f:
        d = f.readlines()
    d = list(map(lambda x: list(x.strip()), d))
    d = list(map(lambda x: list(map(int, x)), d))

    N = 50
    strSum = ''
    carry = 0
    sumResult = 0

    for k in range(N):
        r = list(map(lambda x: x[-k-1], d))
        [carry, sumResult] = sumCol(r, carry)
        strSum = str(sumResult) + strSum

    strSum = str(carry) + strSum
    print(strSum[0:10])

if __name__ == '__main__':
    euler13()

