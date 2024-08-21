#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

// Function to generate primes up to a given limit using the Sieve of Eratosthenes
std::vector<long long> generate_primes_up_to(long long limit) {
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (long long i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    std::vector<long long> primes;
    for (long long i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// Function to calculate the start and end indexes of a given row using triangular numbers
std::pair<long long, long long> get_row_bounds(long long row) {
    long long start = (row * (row - 1)) / 2 + 1;
    long long end = start + row - 1;
    return {start, end};
}

// Function to generate the list of primes in a row by marking non-primes using the primes up to sqrt(end of row)
std::vector<long long> generate_primes_in_row(long long start, long long end) {
    long long limit = std::sqrt(end);
    std::vector<long long> small_primes = generate_primes_up_to(limit);
    
    std::vector<bool> is_prime(end - start + 1, true);
    
    for (long long prime : small_primes) {
        long long first_multiple = std::max(prime * prime, (start + prime - 1) / prime * prime);
        for (long long j = first_multiple; j <= end; j += prime) {
            is_prime[j - start] = false;
        }
    }
    
    std::vector<long long> primes_in_row;
    for (long long i = 0; i <= end - start; ++i) {
        if (is_prime[i]) {
            primes_in_row.push_back(start + i);
        }
    }
    
    return primes_in_row;
}

// Function to get adjacent numbers in the triangle, including directly above and below
std::vector<long long> get_adjacent(long long index, long long row) {
    std::vector<long long> adjacents;
    auto [start, end] = get_row_bounds(row);
    
    if (index > start) adjacents.push_back(index - 1); // left
    if (index < end) adjacents.push_back(index + 1);   // right
    
    auto [prev_start, prev_end] = get_row_bounds(row - 1);
    auto [next_start, next_end] = get_row_bounds(row + 1);
    
    if (index - row >= prev_start && index - row <= prev_end) adjacents.push_back(index - row);         // top-left
    if (index - row + 1 >= prev_start && index - row + 1 <= prev_end) adjacents.push_back(index - row + 1); // top-right
    if (index + row >= next_start && index + row <= next_end) adjacents.push_back(index + row);         // bottom-left
    if (index + row + 1 >= next_start && index + row + 1 <= next_end) adjacents.push_back(index + row + 1); // bottom-right

    // Directly above and below
    if (index - row >= prev_start && index - row <= prev_end) adjacents.push_back(index - row); // directly above
    if (index + row >= next_start && index + row <= next_end) adjacents.push_back(index + row); // directly below

    return adjacents;
}

// Function to check if a number is part of a prime triplet considering adjacent numbers
bool is_prime_triplet(long long index, long long row, const std::unordered_set<long long>& primes_set) {
    auto adjacents = get_adjacent(index, row);
    int prime_count = 0;
    
    for (auto adj : adjacents) {
        if (primes_set.find(adj) != primes_set.end()) {
            prime_count++;
        }
    }
    
    // If the current number has at least two prime neighbors
    return prime_count >= 2;
}

// Function to calculate S(n)
long long S(long long n) {
    long long sum = 0;
    auto [start, end] = get_row_bounds(n);
    
    // Step 1: Generate primes in the current row
    std::vector<long long> primes_in_row = generate_primes_in_row(start, end);
    std::unordered_set<long long> primes_set(primes_in_row.begin(), primes_in_row.end());
    
    // Step 2: Check for prime triplets centered on primes in the current row
    for (auto prime : primes_in_row) {
        if (is_prime_triplet(prime, n, primes_set)) {
            sum += prime;
        }
    }
    
    // Step 3: Check for prime triplets involving adjacent rows
    for (auto prime : primes_in_row) {
        auto adjacents = get_adjacent(prime, n);
        for (auto adj : adjacents) {
            if (primes_set.find(adj) != primes_set.end()) {
                long long adj_row = (adj < prime) ? n - 1 : n + 1;
                if (is_prime_triplet(adj, adj_row, primes_set)) {
                    sum += prime;
                    break;
                }
            }
        }
    }
    
    return sum;
}

int main() {
    long long result = S(5678027) + S(7208785);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
