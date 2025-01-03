# Author: Bruce Hart <bruce.hart@gmail.com>
# The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
# Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
# (Please note that the palindromic number, in either base, may not include leading zeros.)

def isPalindrome(x): 
    return str(x) == str(x)[::-1]

def checkDualPalindrome(x): 
    return isPalindrome(str(x)) and isPalindrome(bin(x)[2:])

def euler36():
    print(sum(filter(checkDualPalindrome, range(10**6))))  # Changed xrange to range for Python 3

if __name__ == '__main__':
    euler36()
