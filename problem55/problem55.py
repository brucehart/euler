def reverse_number(n):
    """Returns the reverse of the given number."""
    return int(str(n)[::-1])

def is_palindrome(n):
    """Checks if the given number is a palindrome."""
    return str(n) == str(n)[::-1]

def is_lychrel(n, max_iterations=50):
    """Determines if a number is a Lychrel number within a given number of iterations."""
    for _ in range(max_iterations):
        n += reverse_number(n)
        if is_palindrome(n):
            return False
    return True

def count_lychrel_numbers(limit=10000):
    """Counts how many Lychrel numbers are there below the given limit."""
    lychrel_count = 0
    for i in range(limit):
        if is_lychrel(i):
            lychrel_count += 1
    return lychrel_count

# Main
limit = 10000
lychrel_numbers_count = count_lychrel_numbers(limit)
print(f"There are {lychrel_numbers_count} Lychrel numbers below {limit}.")
