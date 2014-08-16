# -*- coding: utf-8 -*-
#Author: Bruce Hart <bruce.hart@gmail.com>

#The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:
#
#1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
#
#By converting each letter in a word to a number corresponding to its alphabetical position and
# adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10.
# If the word value is a triangle number then we shall call the word a triangle word.
#
#Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common
# English words, how many are triangle words?

import time


def build_triangle_numbers():
    val_max = 200*26 #support up to 20 character words

    output_list = []

    n = 0
    val = 0

    while(val < val_max):
        val = 0.5*n*(n+1)
        output_list.append(int(val))
        n = n+1

    return output_list

def word_value(word):
    word = word.upper()
    chars = list(word)

    return sum(map(lambda x: ord(x) - ord("A") + 1, chars))

def euler42():
    f = open('words.txt', 'r')
    words = f.read()
    words = words.replace("\"", "")
    words = words.split(",")
    words = map(lambda x: x.strip(), words)

    tri_nums = build_triangle_numbers()

    word_vals = map(word_value, words)
    word_vals = filter(lambda x: x in tri_nums, word_vals)

    print len(word_vals)




if __name__ == '__main__':
    time.clock()
    euler42()
    print "Executed in {0} sec".format(time.clock())