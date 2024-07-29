import math
from decimal import Decimal, getcontext

# Set the precision for Decimal calculations
getcontext().prec = 30

# Function to compute the sequence and concatenation tau from theta using Decimal
def compute_tau(theta, length):
    b1 = Decimal(theta)
    tau = str(math.floor(b1)) + "."

    while len(tau) < (length + 2):  # Adjusting to account for the initial "2."
        floor_b1 = math.floor(b1)
        bn = Decimal(floor_b1) * (b1 - Decimal(floor_b1) + Decimal(1))
        tau += str(math.floor(bn))
        b1 = bn

    return Decimal(tau[:length + 1])

# Function to construct theta digit by digit using Decimal
def construct_theta(alpha, beta, precision):
    theta = Decimal(alpha)
    increment = Decimal('0.1')
    for decimal_place in range(1, precision + 1):
        found_digit = False
        for digit in range(10):
            test_theta = theta + digit * increment
            tau = compute_tau(test_theta, decimal_place + 1)
            if int(test_theta * 10**decimal_place) == int(tau * 10**decimal_place):
                theta = test_theta
                found_digit = True
                break
        if not found_digit:
            raise ValueError(f"Could not find a valid digit at decimal place {decimal_place}. "
                             f"Theta: {theta:.24f}, Tau: {tau:.24f}")
        increment /= 10
        theta = round(theta, decimal_place)
    return theta

# Define the lower bound alpha and upper bound beta
alpha = Decimal('2.0')
beta = Decimal('3.0')
precision = 24

# Find the value of theta
try:
    theta = construct_theta(alpha, beta, precision)
    print(f'{theta:.24f}')
except ValueError as e:
    print(e)
