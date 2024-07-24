def has_same_digits(n, multiples):
    sorted_n = sorted(str(n))
    for multiple in multiples:
        if sorted(str(n * multiple)) != sorted_n:
            return False
    return True

def find_smallest_permuted_multiple():
    x = 1
    while True:
        if has_same_digits(x, [2, 3, 4, 5, 6]):
            return x
        x += 1

result = find_smallest_permuted_multiple()
print(f"The smallest positive integer x such that 2x, 3x, 4x, 5x, and 6x contain the same digits is: {result}")
