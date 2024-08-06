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
    dp = [[float('inf')] * cols for _ in range(rows)]

    # Initialize the first column (starting points)
    for i in range(rows):
        dp[i][0] = matrix[i][0]

    for j in range(1, cols):
        for i in range(rows):
            # Update the dp value for moving right from the same row
            dp[i][j] = min(dp[i][j], dp[i][j-1] + matrix[i][j])

        for i in range(rows):
            # Update the dp value for moving up from the row below
            if i > 0:
                dp[i][j] = min(dp[i][j], dp[i-1][j] + matrix[i][j])

        for i in range(rows-1, -1, -1):
            # Update the dp value for moving down from the row above
            if i < rows - 1:
                dp[i][j] = min(dp[i][j], dp[i+1][j] + matrix[i][j])

    # Find the minimal path sum in the last column
    minimal_sum = float('inf')
    for i in range(rows):
        minimal_sum = min(minimal_sum, dp[i][cols-1])

    return minimal_sum

# Read the matrix from the file
matrix = read_matrix("0082_matrix.txt")

# Calculate the minimal path sum for the provided matrix
minimal_path_sum_result = minimal_path_sum(matrix)
print(minimal_path_sum_result)
