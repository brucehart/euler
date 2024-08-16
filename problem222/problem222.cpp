#if defined(__GNUC__) || defined(__clang__)
    #define USE_BUILTIN_POPCOUNT
#endif

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <limits>
#include <iomanip>  // For std::fixed and std::setprecision

// Function to count the number of set bits (popcount) without using compiler-specific functions
int count_set_bits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

std::vector<double> radii;  // Sphere radii in micrometers
std::vector<std::vector<double>> min_lengths;  // Minimum achievable lengths

// Function to find the minimum length for fitting a set of spheres in a cylindrical tube
double find_minimum_length(int current_index, int sphere_set) {
    if ((sphere_set & (1 << current_index)) == 0)
        throw std::invalid_argument("Invalid sphere index.");

    // Check if the value has already been computed
    if (min_lengths[current_index][sphere_set] == 0) {
        double result;

        // If only one sphere is left, this sphere is rightmost
#ifdef USE_BUILTIN_POPCOUNT
        if (__builtin_popcount(sphere_set) == 1) 
#else
        if (count_set_bits(sphere_set) == 1)  // Use custom popcount function
#endif
            result = radii[current_index];
        else {
            result = std::numeric_limits<double>::infinity();
            int new_sphere_set = sphere_set ^ (1 << current_index);

            // Iterate through possible next spheres
            for (int i = 0; i < radii.size(); i++) {
                if ((new_sphere_set & (1 << i)) == 0)
                    continue;
                
                // Calculate the distance between spheres
                double temp = std::sqrt((radii[i] + radii[current_index] - 50000) * 200000);
                temp += find_minimum_length(i, new_sphere_set);
                result = std::min(temp, result);
            }
        }
        min_lengths[current_index][sphere_set] = result;
    }
    return min_lengths[current_index][sphere_set];
}

int main() {
    radii.resize(21);  // Sphere radii from 30000 to 50000 micrometers

    // Initialize radii values
    for (int i = 0; i < radii.size(); i++)
        radii[i] = (i + 30) * 1000;

    // Initialize min_lengths table
    min_lengths.resize(radii.size(), std::vector<double>(1 << radii.size(), 0));

    double min_value = std::numeric_limits<double>::infinity();

    // Calculate the minimum length required to fit all spheres
    for (int i = 0; i < radii.size(); i++)
        min_value = std::min(find_minimum_length(i, (1 << radii.size()) - 1) + radii[i], min_value);

    // Print the result as a fixed-point number with no scientific notation
    std::cout << std::fixed << std::setprecision(0) << std::round(min_value) << std::endl;
    return 0;
}
