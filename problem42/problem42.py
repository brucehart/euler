# -*- coding: utf-8 -*-
# Author: Bruce Hart <bruce.hart@gmail.com>

# The nth term of the sequence of triangle numbers is given by, tn = 0.5*n(n+1); so the first ten triangle numbers are:
#
# 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
#
# By converting each letter in a word to a number corresponding to its alphabetical position and
# adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10.
# If the word value is a triangle number then we shall call the word a triangle word.
#
# Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common
# English words, how many are triangle words?

def build_triangle_numbers():
    val_max = 200*26  # Support up to 20 character words

    output_list = []

    n = 0
    val = 0

    while val < val_max:
        val = 0.5 * n * (n + 1)
        output_list.append(int(val))
        n += 1

    return output_list

def word_value(word):
    word = word.upper()

    return sum(ord(char) - ord('A') + 1 for char in word)

def euler42():
    with open('words.txt', 'r') as f:
        words = f.read()
        words = words.replace("\"", "")
        words = words.split(",")
        words = map(str.strip, words)

    tri_nums = set(build_triangle_numbers())

    word_vals = map(word_value, words)
    triangle_word_count = sum(1 for value in word_vals if value in tri_nums)

    print(triangle_word_count)

if __name__ == '__main__':
    euler42()
