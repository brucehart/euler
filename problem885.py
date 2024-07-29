def sorted_digits_sum(n, modulo):
    from itertools import combinations_with_replacement

    def f(d):
        sorted_digits = ''.join(sorted(str(d)))
        return int(sorted_digits.lstrip('0'))

    # Cache for storing intermediate results
    dp = {}

    def sum_of_sorted_digits(length):
        if length in dp:
            return dp[length]
        
        total_sum = 0
        digits = '123456789'
        
        for comb in combinations_with_replacement(digits, length):
            num = int(''.join(comb))
            total_sum += f(num)
            total_sum %= modulo
        
        dp[length] = total_sum
        return total_sum
    
    # Total sum for all lengths from 1 to n
    total = 0
    for i in range(1, n + 1):
        total += sum_of_sorted_digits(i)
        total %= modulo
    
    return total

# Constants
MODULO = 1123455689

# Calculate S(18) % MODULO
result = sorted_digits_sum(18, MODULO)
print(result)
