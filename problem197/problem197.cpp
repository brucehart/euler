#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>

// Function f as defined in the problem
double f(double x) {
    // Compute 2^(30.403243784 - x^2), take the floor, and scale by 1e-9
    return std::floor(std::pow(2.0, 30.403243784 - x * x)) * 1e-9;
}

int main() {
    // Initial value of the sequence
    double current = -1.0;

    // Array to store the last four values for detecting convergence
    std::array<double, 4> prev = {0.0, 0.0, 0.0, 0.0};

    // Convergence threshold
    const double epsilon = 1e-10;

    // Index to keep track of the current position in the circular buffer
    int index = 0;

    while (true) {
        // Update the circular buffer with the current value
        prev[index % 4] = current;

        // Compute the next value in the sequence
        double next = f(current);

        // Calculate the difference (delta) to check for convergence
        // (prev0 + next) - (prev2 + prev3)
        double delta = std::fabs((prev[index % 4] + next) - (prev[(index + 1) % 4] + prev[(index + 2) % 4]));

        // If the change is below the threshold, convergence is achieved
        if (delta < epsilon) {
            // Compute the final result: u_n + u_{n+1}
            double result = prev[index % 4] + next;
            // Output the result with fixed notation and 9 decimal places
            std::cout << std::fixed << std::setprecision(9) << result << std::endl;
            break;
        }

        // Update current for the next iteration
        current = next;

        // Move to the next position in the circular buffer
        index++;
    }

    return 0;
}
