#include <iostream>
#include <cmath>
#include <tuple>

// Function to compute the next point of reflection
std::tuple<double, double, double> next_point(double point_x, double point_y, double incoming_gradient) {
    // normal_gradient = gradient of the line through which the beam is reflected
    // outgoing_gradient = gradient of the reflected line
    double normal_gradient = point_y / (4 * point_x);
    double s2 = 2 * normal_gradient / (1 + normal_gradient * normal_gradient);
    double c2 = (1 - normal_gradient * normal_gradient) / (1 + normal_gradient * normal_gradient);
    double outgoing_gradient = (s2 - c2 * incoming_gradient) / (c2 + s2 * incoming_gradient);

    // Solve the simultaneous equations to find the next point
    // y^2 + 4x^2 = 100
    // y - b = m * (x - a)
    // ==> A x^2 + B x + C = 0
    double quadratic_term = outgoing_gradient * outgoing_gradient + 4;
    double linear_term = 2 * outgoing_gradient * (point_y - outgoing_gradient * point_x);
    double constant_term = (point_y - outgoing_gradient * point_x) * (point_y - outgoing_gradient * point_x) - 100;

    double x_minus = (-linear_term - std::sqrt(linear_term * linear_term - 4 * quadratic_term * constant_term)) / (2 * quadratic_term);
    double x_plus = (-linear_term + std::sqrt(linear_term * linear_term - 4 * quadratic_term * constant_term)) / (2 * quadratic_term);

    // Two solutions, one of which is our input point
    double next_x = std::abs(x_plus - point_x) < 1e-9 ? x_minus : x_plus;
    double next_y = point_y + outgoing_gradient * (next_x - point_x);

    return {next_x, next_y, outgoing_gradient};
}

int main() {
    int num_reflections = 0;
    double point_x = 1.4;
    double point_y = -9.6;
    double gradient = (10.1 - point_y) / (0.0 - point_x);

    // Continue until the beam exits the white cell
    while (!(point_x >= -0.01 && point_x <= 0.01 && point_y > 0)) {
        std::tie(point_x, point_y, gradient) = next_point(point_x, point_y, gradient);
        num_reflections++;
    }

    std::cout << num_reflections << std::endl;

    return 0;
}
