def construct_tree_path(n):
    path = []
    current = n
    while current > 1:
        path.append(current)
        if current % 2 == 0:
            current = current // 2
        else:
            current = (current - 1) // 2
    path.append(1)
    return path[::-1]

def f(n, k):
    path = construct_tree_path(n)
    return sum(path[:path.index(k) + 1])

# Function to handle large inputs efficiently
def large_f(n, g):
    path_n = construct_tree_path(n)
    path_g = construct_tree_path(g)
    return sum(path_n) * len(path_g)

# Example usage
n = 10**17
g = 17
result = large_f(n, g)
print(result)
