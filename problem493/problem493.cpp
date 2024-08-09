#include <iostream>
#include <cmath>

int main() {
    // Constants for the problem
    int total_balls = 70; // Total number of balls
    int balls_per_color = 10; // Balls per color
    int draw_count = 20; // Balls to be drawn
    int num_colors = 7; // Number of colors

    double expected_distinct_colors = 0.0;

    // Calculate the expected number of distinct colors
    for (int i = 0; i < num_colors; ++i) {
        double probability_color_not_drawn = 1.0;
        
        // Calculate the probability that a particular color is not drawn
        for (int j = 0; j < draw_count; ++j) {
            probability_color_not_drawn *= static_cast<double>(total_balls - balls_per_color - j) / (total_balls - j);
        }

        // The probability that the color is drawn at least once
        double probability_color_drawn = 1.0 - probability_color_not_drawn;

        // Add to the expected number of distinct colors
        expected_distinct_colors += probability_color_drawn;
    }

    // Print the result with 9 decimal places
    std::cout.precision(9);
    std::cout << std::fixed << expected_distinct_colors << std::endl;

    return 0;
}
