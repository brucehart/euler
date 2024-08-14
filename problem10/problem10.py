def build_prime_list(N):
    """ Efficiently generate a boolean list indicating prime status of each number up to N. """
    is_prime = [True] * (N + 1)
    is_prime[0] = is_prime[1] = False  # 0 and 1 are not prime numbers

    for start in range(2, int(N**0.5) + 1):
        if is_prime[start]:
            for multiple in range(start*start, N + 1, start):
                is_prime[multiple] = False
    return is_prime

def is_prime(x, prime_list=None):
    """ Determine if a number x is prime, optionally using a pre-computed list of prime status. """
    if prime_list:
        return prime_list[x]  # Return pre-computed prime status if prime_list is provided
    if x <= 1:
        return False
    if x <= 3:
        return True  # 2 and 3 are prime numbers
    if x % 2 == 0 or x % 3 == 0:
        return False  # Exclude even numbers and multiples of 3 quickly
    i = 5
    while i * i <= x:
        if x % i == 0 or x % (i + 2) == 0:
            return False
        i += 6
    return True

def euler10():
    D = 2000000
    prime_list = build_prime_list(D)
    sum_of_primes = sum(x for x in range(1, D + 1) if is_prime(x, prime_list))
    print(sum_of_primes)

if __name__ == '__main__':
    euler10()
