import math

# Define the constant N
N = 10**12

def is_S_number(s, l):
    """
    Check if a number l can be split into parts that sum up to s
    """
    pwr10 = 10
    while True:
        right = l % pwr10
        if right > s:
            return False
        left = l // pwr10
        if right + left == s:
            return True
        if left < 10:
            return False
        if s > right and is_S_number(s - right, left):
            return True
        pwr10 *= 10

def T(N):
    """
    Calculate the sum of all S-numbers less than or equal to N
    """
    total_sum = 0
    max_sn = int(math.sqrt(N))  # Calculate the maximum square root
    for sn in range(4, max_sn + 1):
        n = sn * sn
        if is_S_number(sn, n):
            total_sum += n
    return total_sum

# Calculate and print the result
print(T(N))
