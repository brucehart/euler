#include <iostream>
#include <vector>
#include <cmath>

std::vector<long long> generate_fibonacci_up_to(long long limit) {
    std::vector<long long> fibonacci = {1, 2};
    while (true) {
        long long next_fib = fibonacci.back() + fibonacci[fibonacci.size() - 2];
        if (next_fib > limit) break;
        fibonacci.push_back(next_fib);
    }
    return fibonacci;
}

long long count_combinations(long long limit, const std::vector<long long>& fibonacci, long long running_sum, int index) {
    if (limit == 0) return 1;
    if (index < 0 || limit < 0) return 0;

    long long current_fib = fibonacci[index];
    long long remaining_sum = running_sum - current_fib;

    // If sum of smaller numbers is less than (limit - running_sum), use the 2^n optimization
    if (remaining_sum <= limit - current_fib) {
        return static_cast<long long>(std::pow(2, index + 1));
    }

    // Recursive call: include current Fibonacci number and exclude it
    return count_combinations(limit - current_fib, fibonacci, running_sum - current_fib, index - 1) +
           count_combinations(limit, fibonacci, running_sum - current_fib, index - 1);
}

int main() {
    const long long limit = 10000000000000LL; // 10^13
    std::vector<long long> fibonacci = generate_fibonacci_up_to(limit);

    long long running_sum = 0;
    for (long long f : fibonacci) {
        running_sum += f;
    }

    long long result = count_combinations(limit, fibonacci, running_sum, fibonacci.size() - 1);

    std::cout << result << std::endl;

    return 0;
}
