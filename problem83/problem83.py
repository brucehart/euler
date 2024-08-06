import heapq

def read_matrix(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        matrix = []
        for line in lines:
            row = list(map(int, line.strip().split(',')))
            matrix.append(row)
    return matrix

def minimal_path_sum(matrix):
    rows = len(matrix)
    cols = len(matrix[0])
    
    # Directions for movement: up, down, left, right
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    # Priority queue to store (cost, x, y)
    pq = [(matrix[0][0], 0, 0)]
    
    # Set to keep track of visited nodes
    visited = set()
    
    while pq:
        cost, x, y = heapq.heappop(pq)
        
        # If we reached the bottom-right corner, return the cost
        if (x, y) == (rows-1, cols-1):
            return cost
        
        # If this node is already visited, skip it
        if (x, y) in visited:
            continue
        
        # Mark the node as visited
        visited.add((x, y))
        
        # Explore neighbors
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            
            if 0 <= nx < rows and 0 <= ny < cols and (nx, ny) not in visited:
                heapq.heappush(pq, (cost + matrix[nx][ny], nx, ny))
    
    return -1  # In case there is no path (should not happen with given problem constraints)

# Read the matrix from the file
matrix = read_matrix("0083_matrix.txt")

# Calculate the minimal path sum for the provided matrix
minimal_path_sum_result = minimal_path_sum(matrix)
print(minimal_path_sum_result)
