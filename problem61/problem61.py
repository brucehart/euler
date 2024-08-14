from itertools import permutations
from collections import defaultdict

# Define the functions for each polygonal number type
def triangle(n):
    return n * (n + 1) // 2

def square(n):
    return n * n

def pentagonal(n):
    return n * (3 * n - 1) // 2

def hexagonal(n):
    return n * (2 * n - 1)

def heptagonal(n):
    return n * (5 * n - 3) // 2

def octagonal(n):
    return n * (3 * n - 2)

# Generate polygonal numbers in the range [1000, 9999]
def generate_polygonal_numbers(p_func):
    return [p_func(n) for n in range(1, 200) if 1000 <= p_func(n) <= 9999]

# Generate the numbers using the updated function
triangle_numbers = generate_polygonal_numbers(triangle)
square_numbers = generate_polygonal_numbers(square)
pentagonal_numbers = generate_polygonal_numbers(pentagonal)
hexagonal_numbers = generate_polygonal_numbers(hexagonal)
heptagonal_numbers = generate_polygonal_numbers(heptagonal)
octagonal_numbers = generate_polygonal_numbers(octagonal)

polygonal_numbers = {
    'triangle': triangle_numbers,
    'square': square_numbers,
    'pentagonal': pentagonal_numbers,
    'hexagonal': hexagonal_numbers,
    'heptagonal': heptagonal_numbers,
    'octagonal': octagonal_numbers
}

# Helper function to find if two numbers can form a cyclic link
def can_link(a, b):
    return str(a)[2:] == str(b)[:2]

# Establish links between numbers of different polygonal types
pair_links = defaultdict(lambda: defaultdict(list))

for type1, numbers1 in polygonal_numbers.items():
    for type2, numbers2 in polygonal_numbers.items():
        if type1 != type2:
            for num1 in numbers1:
                for num2 in numbers2:
                    if can_link(num1, num2):
                        pair_links[type1][type2].append((num1, num2))

# Structured DFS with detailed debug information for each step
def find_cyclic_set():
    for start_type, numbers in polygonal_numbers.items():
        for start_num in numbers:
            stack = [(start_type, start_num, [(start_type, start_num)], set([start_type]))]
            while stack:
                current_type, current_num, path, used_types = stack.pop()
                if len(path) == 6:
                    if can_link(current_num, path[0][1]):
                        return path
                    continue
                for next_type, links in pair_links[current_type].items():
                    if next_type not in used_types:
                        for num1, num2 in links:
                            if num1 == current_num:
                                new_path = path + [(next_type, num2)]
                                new_used_types = used_types | {next_type}
                                stack.append((next_type, num2, new_path, new_used_types))
    return None

# Search for a cyclic set of six values
cyclic_set = find_cyclic_set()

# Add values together and print the solution
if cyclic_set:
    cyclic_values = [num for _, num in cyclic_set]
    cyclic_sum = sum(cyclic_values)
    #print("Cyclic Set:", cyclic_set)
    #print("Sum of Cyclic Set:", cyclic_sum)
    print(cyclic_sum)
else:
    print("No cyclic set found")

