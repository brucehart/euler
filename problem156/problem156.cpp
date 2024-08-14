#include <iostream>
#include <vector>

// Function to count occurrences of a digit in a single number
int count_digit(int number, int digit) {
    int count = 0;
    while (number > 0) {
        int remainder = number % 10;
        if (remainder == digit) {
            count++;
        }
        number /= 10;
    }
    return count;
}

// Function to calculate the total count of a digit from 0 to n
long long count_digit_occurrences(long long n, int digit) {
    long long count = 0;
    long long factor = 1;
    while (n / factor != 0) {
        long long lower_number = n - (n / factor) * factor;
        long long current_digit = (n / factor) % 10;
        long long higher_number = n / (factor * 10);

        if (current_digit < digit) {
            count += higher_number * factor;
        } else if (current_digit == digit) {
            count += higher_number * factor + lower_number + 1;
        } else {
            count += (higher_number + 1) * factor;
        }
        factor *= 10;
    }
    return count;
}

// Function to perform binary search and find all n where count_digit_occurrences(n, digit) == n
void binary_search_and_sum(long long lower, long long upper, int digit, std::vector<long long> &found) {
    if (lower + 1 == upper) {
        if (count_digit_occurrences(lower, digit) == lower) {
            found.push_back(lower);
        }
        return;
    }

    long long middle = (lower + upper) / 2;
    long long lower_value = count_digit_occurrences(lower, digit);
    long long upper_value = count_digit_occurrences(upper, digit);
    long long middle_value = count_digit_occurrences(middle, digit);

    if (middle_value >= lower && middle >= lower_value) {
        binary_search_and_sum(lower, middle, digit, found);
    }
    if (upper_value >= middle && upper >= middle_value) {
        binary_search_and_sum(middle, upper, digit, found);
    }
}

// Main function to solve the problem
int main() {
    long long total_sum = 0;

    for (int digit = 1; digit <= 9; ++digit) {
        std::vector<long long> found;
        binary_search_and_sum(1, 100000000000LL, digit, found);
        long long digit_sum = 0;
        for (long long n : found) {
            digit_sum += n;
        }
        
        total_sum += digit_sum;
    }

    std::cout << total_sum << std::endl;

    return 0;
}
