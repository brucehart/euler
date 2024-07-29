def compute_C(n):
    # Initialize the base cases
    C = [0] * (n + 1)
    C[0] = C[1] = C[2] = 1
    C[3] = 2

    # Compute values using the recurrence relation
    for i in range(4, n+1):
        C[i] = 2 * C[i - 1] - C[i - 2] + C[i - 4]
    
    return C[n]

# Compute C(50)
result = compute_C(50)
print(result)
