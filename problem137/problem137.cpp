#include <iostream>

// Function to compute the nth Fibonacci number
unsigned long long Fibonacci(int n) {
    if (n <= 1)
        return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main() {
    const int n = 15;
    unsigned long long sequence_value = 0;

    unsigned long long F_2n = Fibonacci(2 * n);
    unsigned long long F_2n_plus_1 = Fibonacci(2 * n + 1);
    sequence_value = F_2n * F_2n_plus_1;   
  
    std::cout << sequence_value << std::endl;

    return 0;
}
