#Author : Bruce Hart <bruce.hart@gmail.com>

#A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 * 99.
#
#Find the largest palindrome made from the product of two 3-digit numbers.

def isPalindrome(numVal):
    strVal = str(numVal)

    for n in range(len(strVal)//2+1):
        if (strVal[n] != strVal[-1*(n+1)]):
            return False

    return True

def getProduct():
    for a in xrange(100,1000):
        for b in xrange(100,1000):
            yield a*b


palindromes = filter(isPalindrome,getProduct())
#print(palindromes)
max_palindrome = max(palindromes)

print max_palindrome