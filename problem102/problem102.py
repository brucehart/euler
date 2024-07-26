# Function to compute the sign of the cross product of two vectors
def sign_of_cross_product(x1, y1, x2, y2):
    return x1 * y2 - y1 * x2

# Function to determine if the origin is inside the triangle using the cross product method
def contains_origin_cross_product(triangle):
    x1, y1, x2, y2, x3, y3 = triangle
    cp1 = sign_of_cross_product(x1, y1, x2, y2)
    cp2 = sign_of_cross_product(x2, y2, x3, y3)
    cp3 = sign_of_cross_product(x3, y3, x1, y1)
    
    return (cp1 >= 0 and cp2 >= 0 and cp3 >= 0) or (cp1 <= 0 and cp2 <= 0 and cp3 <= 0)

file_path = "0102_triangles.txt"

with open(file_path, 'r') as file:
    triangles_data = file.readlines()
    
# Read the triangle data and check for each triangle using the cross product method
triangle_count_cross_product = 0

for line in triangles_data:
    triangle = list(map(int, line.strip().split(',')))
    if contains_origin_cross_product(triangle):
        triangle_count_cross_product += 1

print(triangle_count_cross_product)


