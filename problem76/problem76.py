def count_partitions(n):
    partition_counts = [0] * (n + 1)
    partition_counts[0] = 1
    
    for i in range(1, n):
        for j in range(i, n + 1):
            partition_counts[j] += partition_counts[j - i]
    
    return partition_counts[n]

# Calculate the number of partitions for 100
result = count_partitions(100)
print(result)
