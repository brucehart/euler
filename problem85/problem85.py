# Let's analyze the problem and then write a Python script to solve it.

# The problem requires us to find the area of the grid with the nearest solution to two million rectangles.

# The number of rectangles in a grid of size m x n can be calculated using the formula:
# (m * (m + 1) / 2) * (n * (n + 1) / 2)

# We will search for m and n such that the number of rectangles is closest to two million.

target = 2000000

def count_rectangles(m, n):
    return (m * (m + 1) // 2) * (n * (n + 1) // 2)

closest_diff = float('inf')
closest_area = 0

for m in range(1, 2000):  # Range is arbitrary; adjusted based on the problem constraints
    for n in range(1, 2000):
        rectangles = count_rectangles(m, n)
        diff = abs(target - rectangles)
        
        if diff < closest_diff:
            closest_diff = diff
            closest_area = m * n
            
        if rectangles > target:
            break

print(closest_area)
