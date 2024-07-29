import decimal
from decimal import Decimal, getcontext

# Set the precision to ensure we have enough digits
getcontext().prec = 110

def sum_of_first_100_digits(n):
    """Calculate the sum of the first 100 digits of the square root of n, including both sides of the decimal point."""
    sqrt_n = str(Decimal(n).sqrt())
    digits = ''.join(sqrt_n.split('.'))[:100]  # Combine integer and fractional parts and take first 100 digits
    return sum(int(digit) for digit in digits)

# List of the first 100 natural numbers
numbers = list(range(1, 101))

# Remove perfect squares
perfect_squares = {i * i for i in range(1, 11)}
irrational_numbers = [n for n in numbers if n not in perfect_squares]

# Calculate the sum of the first 100 digits for each irrational number
total_sum = sum(sum_of_first_100_digits(n) for n in irrational_numbers)

print(total_sum)
