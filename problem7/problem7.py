def isprime(x):
    if x <= 1:
        return False
    if x <= 3:
        return True  # Returns True for 2 and 3, ignores 1
    if x % 2 == 0 or x % 3 == 0:
        return False
    i = 5
    while i * i <= x:
        if x % i == 0 or x % (i + 2) == 0:
            return False
        i += 6
    return True

def infiniteCount():
    c = 1
    while True:
        c += 1
        yield c

def euler7():
    P = 10001
    count = 0
    for n in infiniteCount():
        if isprime(n):
            count += 1
        if count == P:
            break

    print(n)

if __name__ == '__main__':
    euler7()

