#include <iostream>

int main() {
    int max_perimeter = 1000000000;
    long long prev_value = 1;
    long long value = 2;

    long long perimeters_sum = 0;
    int i = 0;
    long long perimeter = 0;

    // Loop until the perimeter exceeds the maximum allowed perimeter
    while (perimeter <= max_perimeter) {
        perimeters_sum += perimeter;

        prev_value += 2 * value;
        value += prev_value;

        // Calculate the perimeter based on the current iteration
        perimeter = (i % 2 == 0) ? 2 * value + 2 : 2 * value - 2;
        i++;
    }

    // Print the result
    std::cout << perimeters_sum << std::endl;
    return 0;
}
