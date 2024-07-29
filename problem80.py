import decimal
from decimal import Decimal, getcontext

# Set the precision to ensure we have enough decimal places
getcontext().prec = 200

def sum_of_digits(n, num_digits):
    """Calculate the sum of the first num_digits of the decimal part of the square root of n."""
    sqrt_n = str(Decimal(n).sqrt())
    decimal_part = sqrt_n.split('.')[1][:num_digits]
    return sum(int(digit) for digit in decimal_part)

# List of the first 100 natural numbers
numbers = list(range(1, 101))

# Remove perfect squares
perfect_squares = {i * i for i in range(1, 11)}
irrational_numbers = [n for n in numbers if n not in perfect_squares]

print(irrational_numbers)
# Calculate the sum of the first 100 decimal digits for each irrational number
total_sum = sum(sum_of_digits(n, 100) for n in irrational_numbers)

print(total_sum)
