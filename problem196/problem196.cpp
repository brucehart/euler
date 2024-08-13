#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Function to display a progress bar
void display_progress_bar(int progress, int total, int bar_width = 50) {
    float ratio = static_cast<float>(progress) / total;
    int completed = static_cast<int>(ratio * bar_width);

    std::cout << "\r[";
    for (int i = 0; i < bar_width; ++i) {
        if (i < completed) std::cout << "=";
        else std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(ratio * 100.0) << "%";
    std::cout.flush();
}

// Function to determine if a number is prime (reused from previous examples)
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to find all primes in the nth row (reused from previous examples)
std::vector<long long> primes_in_row(int n) {
    long long start = static_cast<long long>(n) * (n - 1) / 2 + 1;
    long long end = start + n;
    std::vector<long long> primes;
    for (long long i = start; i < end; ++i) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to get odd neighbors of a number in the triangle (reused from previous examples)
std::vector<long long> odd_neighbors_of(long long n) {
    auto row_of = [](long long a) -> int {
        return static_cast<int>(std::ceil((-1 + std::sqrt(1 + 8 * a)) / 2));
    };
    int row = row_of(n);
    auto is_neighbor_in_adjacent_row = [row_of, row](long long a) -> bool {
        return std::abs(row - row_of(a)) == 1;
    };
    std::vector<long long> possible_neighbors;
    if (row % 2 == 1) {
        possible_neighbors = {n - row + 1, n + row - 1, n + row + 1};
    } else {
        possible_neighbors = {n - row, n - row - 2, n + row};
    }
    std::vector<long long> odd_neighbors;
    std::copy_if(possible_neighbors.begin(), possible_neighbors.end(), std::back_inserter(odd_neighbors), is_neighbor_in_adjacent_row);
    return odd_neighbors;
}

// Function to get odd prime triplets involving a number (reused from previous examples)
std::vector<std::vector<long long>> get_odd_triplets(long long a) {
    std::vector<std::vector<long long>> triplets;
    for (long long b : odd_neighbors_of(a)) {
        for (long long c : odd_neighbors_of(b)) {
            if (a != c) {
                triplets.push_back({a, b, c});
            }
        }
    }
    return triplets;
}

// Function to check if a number is part of a prime triplet (reused from previous examples)
bool is_part_of_a_prime_triplet(long long n) {
    for (const auto& triplet : get_odd_triplets(n)) {
        if (std::all_of(triplet.begin(), triplet.end(), is_prime)) {
            return true;
        }
    }
    return false;
}

// Function to sum up elements in a given row with two prime neighbors
long long sum_prime_triplets_in_row(int n) {
    std::vector<long long> primes = primes_in_row(n);
    long long sum = 0;
    int total_primes = primes.size();

    for (int i = 0; i < total_primes; ++i) {
        long long prime = primes[i];
        if (is_part_of_a_prime_triplet(prime)) {
            sum += prime;
        }
        // Update the progress bar
        display_progress_bar(i + 1, total_primes);
    }
    std::cout << std::endl; // Move to the next line after the progress bar completes
    return sum;
}

int main() {
    // Example usage
    long long result = sum_prime_triplets_in_row(5678027) + sum_prime_triplets_in_row(7208785);
    std::cout << "Result = " << result << std::endl;

    return 0;
}
