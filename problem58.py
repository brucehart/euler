def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def find_spiral_side_length(threshold):
    side_length = 1
    number = 1
    prime_count = 0
    total_diagonals = 1
    
    while True:
        side_length += 2
        corners = [number + i * (side_length - 1) for i in range(1, 5)]
        prime_count += sum(1 for corner in corners if is_prime(corner))
        total_diagonals += 4
        number = corners[-1]
        
        if prime_count / total_diagonals < threshold:
            return side_length

# Find the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%
side_length_below_10_percent = find_spiral_side_length(0.1)
side_length_below_10_percent
