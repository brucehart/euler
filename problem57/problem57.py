def count_expansions_with_more_digits(num_expansions):
    """
    Count the number of fraction expansions where the numerator has more digits than the denominator.
    
    Parameters:
        num_expansions (int): The number of expansions to consider.
    
    Returns:
        int: The count of expansions where the numerator has more digits.
    """
    count = 0
    num, denom = 3, 2  # Starting with the first expansion (3/2)

    for _ in range(1, num_expansions):
        num, denom = num + 2 * denom, num + denom  # Generate the next fraction in the sequence
        if len(str(num)) > len(str(denom)):  # Check if the numerator has more digits than the denominator
            count += 1  # Increment the count if the condition is met

    return count

# Determine the number of expansions where the numerator has more digits than the denominator for the first 1000 expansions
num_expansions = 1000
result = count_expansions_with_more_digits(num_expansions)
print(result)

