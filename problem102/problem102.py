# Function to calculate the area of a triangle using the coordinates of its vertices
def calculate_area(x1, y1, x2, y2, x3, y3):
    return abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0

# Function to determine if the origin is inside the triangle
def contains_origin(triangle):
    x1, y1, x2, y2, x3, y3 = triangle
    total_area = calculate_area(x1, y1, x2, y2, x3, y3)
    area1 = calculate_area(0, 0, x2, y2, x3, y3)
    area2 = calculate_area(x1, y1, 0, 0, x3, y3)
    area3 = calculate_area(x1, y1, x2, y2, 0, 0)
    return total_area == (area1 + area2 + area3)

file_path = "0102_triangles.txt"

with open(file_path, 'r') as file:
    triangles_data = file.readlines()


# Read the triangle data and check for each triangle
triangle_count = 0

for line in triangles_data:
    triangle = list(map(int, line.strip().split(',')))
    if contains_origin(triangle):
        triangle_count += 1

print(triangle_count)
