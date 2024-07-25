from fractions import Fraction

def compute_e_convergent(n):
    e_sequence = [2]
    k = 1
    while len(e_sequence) < n:
        e_sequence.extend([1, 2 * k, 1])
        k += 1

    e_sequence = e_sequence[:n][::-1]

    convergent = Fraction(e_sequence[0])
    for term in e_sequence[1:]:
        convergent = term + 1 / convergent

    return convergent

# Calculate the 100th convergent for e
convergent_100 = compute_e_convergent(100)
numerator_100 = convergent_100.numerator

# Sum the digits of the numerator
sum_of_digits = sum(int(digit) for digit in str(numerator_100))
print(sum_of_digits)
