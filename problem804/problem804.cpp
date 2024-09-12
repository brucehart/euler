#include <iostream>
#include <cmath>
#include <cstdint>

// Function to compute the count of integer solutions for the equation x^2 + 163*y^2 = 4*N
int64_t compute_T(int64_t N) {
    int64_t T = 0; 

    // Calculate the maximum value of y based on the given equation and N
    int64_t Y_max = static_cast<int64_t>(std::sqrt(4.0 * N / 163.0));

    // Iterate over all possible values of y within the range
    for (int64_t y = -Y_max; y <= Y_max; ++y) {
        int64_t y2 = y * y;
        int64_t D_x = 4 * N - 163 * y2; // Calculate the discriminant for x

        // Check if the discriminant is non-negative (meaning real solutions for x exist)
        if (D_x >= 0) {
            double sqrt_D_x = std::sqrt(static_cast<double>(D_x));

            // Calculate the minimum and maximum values of x for the given y
            int64_t x_min = static_cast<int64_t>(std::ceil((-y - sqrt_D_x) / 2.0));
            int64_t x_max = static_cast<int64_t>(std::floor((-y + sqrt_D_x) / 2.0));

            // If there's a valid range for x, add the count of solutions to T
            if (x_max >= x_min) {
                T += x_max - x_min + 1;
            }

            // Special case: when y is 0, we need to avoid overcounting the solution (0, 0)
            if (y == 0) {
                T -= 1;
            }
        }
    }
    return T;
}

int main() {
    int64_t N = 10000000000000000LL; // Set N to 10^16
    int64_t T_N = compute_T(N); // Compute the count of solutions
    std::cout << T_N << std::endl; // Print the result
    return 0;
}