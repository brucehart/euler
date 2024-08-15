def is_prime(n):
    # Returns True if n is a prime number, otherwise False
    if n <= 1:
        return False  # numbers less than 2 are not prime
    if n <= 3:
        return True  # 2 and 3 are prime numbers
    if n % 2 == 0 or n % 3 == 0:
        return False  # multiples of 2 or 3 are not prime
    i = 5
    while i * i <= n:
        # check for factors from 5 onwards, skipping even numbers
        if n % i == 0 or n % (i + 2) == 0:
            return False  # found a factor, n is not prime
        i += 6
    return True  # no factors found, n is prime

def find_spiral_side_length(threshold):
    # Finds the side length of the square spiral for which the ratio of primes along both diagonals first falls below the given threshold
    side_length = 1  # starting side length of spiral
    number = 1  # starting number at center of spiral
    prime_count = 0  # count of prime numbers found on diagonals
    total_diagonals = 1  # total numbers on diagonals
    
    while True:
        side_length += 2  # increase side length by 2 for each layer of spiral
        corners = [number + i * (side_length - 1) for i in range(1, 5)]
        prime_count += sum(1 for corner in corners if is_prime(corner))  # count primes at corners
        total_diagonals += 4  # each layer adds four new diagonal numbers
        number = corners[-1]  # update the starting number for the next layer
        
        if prime_count / total_diagonals < threshold:
            return side_length  # return the side length if ratio falls below threshold

# Find the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%
side_length_below_10_percent = find_spiral_side_length(0.1)
print(side_length_below_10_percent)

