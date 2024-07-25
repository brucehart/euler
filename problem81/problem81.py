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
    # Create a 2D array to store the minimal path sums
    dp = [[0] * cols for _ in range(rows)]
    
    # Initialize the first cell with the value in the matrix
    dp[0][0] = matrix[0][0]
    
    # Initialize the first row (can only come from the left)
    for j in range(1, cols):
        dp[0][j] = dp[0][j-1] + matrix[0][j]
    
    # Initialize the first column (can only come from above)
    for i in range(1, rows):
        dp[i][0] = dp[i-1][0] + matrix[i][0]
    
    # Fill the rest of the dp array
    for i in range(1, rows):
        for j in range(1, cols):
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + matrix[i][j]
    
    # The minimal path sum will be in the bottom-right corner of the dp array
    return dp[rows-1][cols-1]

# Read the matrix from the file
matrix = read_matrix("0081_matrix.txt")

# Calculate the minimal path sum for the provided matrix
minimal_path_sum_result = minimal_path_sum(matrix)
print(minimal_path_sum_result)
