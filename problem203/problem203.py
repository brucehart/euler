import math

def generate_pascals_triangle(rows):
    triangle = [[1]]
    for n in range(1, rows):
        row = [1]
        for k in range(1, n):
            row.append(triangle[n-1][k-1] + triangle[n-1][k])
        row.append(1)
        triangle.append(row)
    return triangle

def is_square_free(n):
    if n < 2:
        return True
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % (i * i) == 0:
            return False
    return True

def main():
    rows = 51
    triangle = generate_pascals_triangle(rows)
    unique_numbers = set()
    for row in triangle:
        unique_numbers.update(row)
    
    square_free_sum = sum(n for n in unique_numbers if is_square_free(n))
    
    return square_free_sum

square_free_sum = main()
print(square_free_sum)
