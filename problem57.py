def count_expansions_with_more_digits(num_expansions):
    count = 0
    num, denom = 3, 2  # Starting with the first expansion (3/2)

    for _ in range(1, num_expansions):
        num, denom = num + 2 * denom, num + denom
        if len(str(num)) > len(str(denom)):
            count += 1

    return count

# We need the first 1000 expansions
num_expansions = 1000
result = count_expansions_with_more_digits(num_expansions)
result
