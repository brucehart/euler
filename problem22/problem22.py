# -*- coding: utf-8 -*-
# Author: Bruce Hart <bruce.hart@gmail.com>

# Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand
# first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name,
# multiply this value by its alphabetical position in the list to obtain a name score.
#
# For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is
# the 938th name in the list. So, COLIN would obtain a score of 938 x 53 = 49714.
#
# What is the total of all the name scores in the file?

def compute_score(name):
    chars = list(name.upper())
    return sum(map(lambda x: ord(x) - ord("A") + 1, chars))

def euler22():
    with open('p022_names.txt', 'r') as f:
        names = f.read()
    
    names = names.replace("\"", "")
    names = names.split(",")
    names = [name.strip() for name in names]
    names = sorted(names)

    name_scores = list(map(compute_score, names))
    total_score = sum((i + 1) * score for i, score in enumerate(name_scores))
    
    print(total_score)

if __name__ == '__main__':
    euler22()

