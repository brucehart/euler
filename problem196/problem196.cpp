#include <iostream>
#include <vector>
#include <cmath>

// Flags indicating whether numbers are prime
std::vector<bool> is_prime_flag;

bool is_prime(unsigned int num) {
    // Check if the number is even
    if ((num & 1) == 0)
        return num == 2;  // 2 is the only even prime
    return is_prime_flag[num >> 1];  // Odd numbers are checked in the flag vector
}

// Generate primes up to the given limit
void sieve_primes(unsigned int limit) {
    const unsigned int half_limit = (limit >> 1) + 1;

    // If the sieve is already large enough, no need to reallocate
    if (is_prime_flag.size() >= half_limit)
        return;

    // Initialize the prime flag vector
    is_prime_flag.resize(half_limit, true);
    is_prime_flag[0] = false;  // 1 is not a prime number

    // Sieve of Eratosthenes algorithm
    for (unsigned int i = 1; 2 * i * i < half_limit; i++) {
        if (is_prime_flag[i]) {
            unsigned int composite_index = 3 * i + 1;
            while (composite_index < half_limit) {
                is_prime_flag[composite_index] = false;
                composite_index += 2 * i + 1;
            }
        }
    }
}

// Calculate the position of a number in a triangular matrix
unsigned long long triangular_position(unsigned int row, unsigned int col) {
    return row + col * (col - 1ULL) / 2;
}

// Flags for primes in the segmented sieve
std::vector<bool> segment_prime_flags;
unsigned long long segment_base = 0;

// Generate primes in a specific segment range [from, to]
void segmented_sieve(unsigned long long from, unsigned long long to) {
    sieve_primes(sqrt(to));  // Generate small primes up to sqrt(to)

    segment_base = from | 1;  // Ensure starting point is odd
    auto range_size = to - from + 1;

    // Initialize the segment prime flag vector
    segment_prime_flags.clear();
    segment_prime_flags.resize(range_size + 1, true);

    // Segmented sieve algorithm
    for (unsigned long long prime = 3; prime * prime <= to; prime += 2) {
        if (is_prime(prime)) {
            auto smallest_multiple = from - (from % prime) + prime;
            if (smallest_multiple % 2 == 0)
                smallest_multiple += prime;
            for (size_t i = smallest_multiple; i <= to; i += 2 * prime)
                segment_prime_flags[(i - segment_base) / 2] = false;
        }
    }
}

// Check if a number is prime in the segmented sieve
bool is_segment_prime(int row, int col) {
    if (row < 1 || row > col)
        return false;

    auto number = triangular_position(row, col);
    if (number % 2 == 0)
        return number == 2;  // 2 is the only even prime

    return segment_prime_flags[(number - segment_base) / 2];
}

// Process a specific row in the triangular matrix
unsigned long long process_row(unsigned int row) {
    auto sieve_start = triangular_position(1, row - 2);
    auto sieve_end = triangular_position(1, row + 3) - 1;

    if (row <= 2)
        sieve_start = 1;

    segmented_sieve(sieve_start, sieve_end);

    std::vector<bool> prime_triplet_flags(segment_prime_flags.size(), false);
    for (unsigned int current_row = row - 1; current_row <= row + 1; current_row++) {
        for (unsigned int current_col = 1; current_col <= current_row; current_col++) {
            if (!is_segment_prime(current_col, current_row))
                continue;

            auto prime_neighbors = 0;
            for (int dx = -1; dx <= +1; dx++)
                for (int dy = -1; dy <= +1; dy++)
                    if (prime_neighbors < 3 && is_segment_prime(current_col + dx, current_row + dy))
                        prime_neighbors++;

            prime_triplet_flags[triangular_position(current_col, current_row) - segment_base] = (prime_neighbors >= 3);
        }
    }

    unsigned long long sum_primes = 0;
    for (unsigned int col = 1; col <= row; col++) {
        auto number = triangular_position(col, row);
        if (!is_segment_prime(col, row))
            continue;

        bool has_prime_triplet_neighbor = false;
        for (int dx = -1; dx <= +1; dx++)
            for (int dy = -1; dy <= +1; dy++)
                has_prime_triplet_neighbor |= prime_triplet_flags[triangular_position(col + dx, row + dy) - segment_base];

        if (has_prime_triplet_neighbor)
            sum_primes += number;
    }

    return sum_primes;
}

int main() {
    std::cout << process_row(5678027) + process_row(7208785) << std::endl;
    return 0;
}
