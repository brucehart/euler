import itertools

def is_pandigital(number, base):
    """
    Check if a number is pandigital in a given base.

    A pandigital number in this context means that all digits from 0 to base-1
    are present at least once in the number when represented in that base.

    Args:
    number (int): The number to check.
    base (int): The base to check in.

    Returns:
    bool: True if the number is pandigital in the given base, False otherwise.
    """
    used = 0
    ALL = (1 << base) - 1  # Bitmask where all bits are set (all digits used)

    # Process each digit of the number
    while number >= base:
        digit = number % base
        used |= 1 << digit  # Mark the digit as used
        number //= base

    # Process the last digit
    used |= 1 << number

    return used == ALL  # Check if all digits are used

# Constants
base = 12
num_results = 10

# Initialize the smallest pandigital number in the given base
start_base = list(range(base))

num_found = 0
total_sum = 0

# Iterate through all permutations of the digits
for perm in itertools.permutations(start_base):
    current = 0
    # Convert the permutation from the given base to an integer
    for digit in perm:
        current = current * base + digit

    # Skip numbers that are not pandigital in base 8 (optimization)
    if base >= 8 and not is_pandigital(current, 8):
        continue

    # Check pandigital property in all bases from 2 to base-1
    is_good = True
    for i in range(base - 1, 1, -1):
        if not is_pandigital(current, i):
            is_good = False
            break

    # If the number is pandigital in all required bases, add it to the sum
    if is_good:
        total_sum += current
        num_found += 1
        # Stop when the required number of results is found
        if num_found == num_results:
            break

# Output the sum of the first num_results pandigital numbers
print(total_sum)
