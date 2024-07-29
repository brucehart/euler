def S(n, mod=1):
    """
    Calculates the sum S(n) = Σ (1/k^2) * ((1-k^2) - (1-k^2)^(n+1)) 
    for k ranging from 1 to n, with modular arithmetic to prevent overflow.

    Args:
        n: The upper limit of the summation.
        mod: The modulus for modular arithmetic (default is 1000000007).

    Returns:
        The calculated sum S(n) modulo `mod`.
    """

    result = 0  # Initialize the sum (no need for float here)
    for k in range(1, n + 1):
        # Modular arithmetic for exponentiation
        base = (1 - k**2) % mod
        exponent = (n + 1) % (mod - 1)  # Fermat's Little Theorem
        term = (pow(k, -2, mod) * (base - pow(base, exponent, mod))) % mod
        result = (result + term) % mod
    return result


# Example usage:
n = 10**6
mod_value = 1000000007
sum_value = S(n, mod_value)
print(f"{sum_value}")
