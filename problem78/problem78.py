def pentagonal_number(k):
    """
    Generate the k-th generalized pentagonal number.
    Generalized pentagonal numbers are given by the formula:
    P(k) = k(3k-1)/2 for k in ...,-2,-1,1,2,...
    """
    return k * (3 * k - 1) // 2

def partition_function_divisible_by_million():
    """
    Find the smallest number n such that the partition function p(n) is divisible by one million.
    The partition function p(n) is computed using a recurrence relation involving generalized pentagonal numbers.
    """
    partitions = [1]  # p(0) = 1 by definition
    n = 1

    while True:
        partition = 0
        k = 1
        pentagonal = pentagonal_number(k)

        # Generate and sum partitions using generalized pentagonal numbers
        while pentagonal <= n:
            sign = (-1) ** (k + 1)  # Alternating sign based on the index k
            partition += sign * partitions[n - pentagonal]

            pentagonal = pentagonal_number(-k)  # Generate the negative k pentagonal number
            if pentagonal <= n:
                partition += sign * partitions[n - pentagonal]

            k += 1
            pentagonal = pentagonal_number(k)  # Generate the next positive k pentagonal number

        partitions.append(partition % 1000000)  # Only keep the last 6 digits

        if partitions[-1] == 0:
            return n

        n += 1

# Pentagonal numbers are used in the partition function because of Euler's pentagonal number theorem, which provides a recurrence relation for partitions. This theorem states that the partition function can be expressed using a series that alternates in sign and involves pentagonal numbers.
# Finding the least value of n for which p(n) is divisible by one million
result = partition_function_divisible_by_million()
print("The least value of n for which p(n) is divisible by one million is:", result)
