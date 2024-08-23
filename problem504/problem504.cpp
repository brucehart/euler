#include <iostream>
#include <cmath>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Function to calculate the number of boundary points on the quadrilateral
// formed by the vertices A(a, 0), B(0, b), C(-c, 0), D(0, -d)
int boundary_points(int a, int b, int c, int d) {
    return gcd(a, b) + gcd(b, c) + gcd(c, d) + gcd(d, a);
}

// Function to calculate the area of the quadrilateral using the Shoelace formula
int area_of_quadrilateral(int a, int b, int c, int d) {
    // The formula gives the area for the quadrilateral formed by the vertices
    // in sequence: (a, 0), (0, b), (-c, 0), (0, -d)
    return a * b + b * c + c * d + d * a;
}

// Function to calculate the number of interior lattice points using Pick's Theorem
int interior_points(int area, int boundary) {
    // Pick's Theorem: Area = I + B/2 - 1
    // Rearranging to find the number of interior points (I):
    return (area - boundary + 2) / 2;
}

// Function to check if a number is a perfect square
bool is_square(int n) {
    int root = static_cast<int>(std::sqrt(n));
    return root * root == n;
}

int main() {
    int m = 100; // The maximum value for a, b, c, and d
    int count = 0; // To count the number of quadrilaterals with a square number of lattice points

    // Iterate over all possible values for a, b, c, and d
    for (int a = 1; a <= m; ++a) {
        for (int b = 1; b <= m; ++b) {
            for (int c = 1; c <= m; ++c) {
                for (int d = 1; d <= m; ++d) {
                    // Calculate boundary points and area
                    int boundary = boundary_points(a, b, c, d);
                    int area = area_of_quadrilateral(a, b, c, d);
                    // Calculate the number of interior points using Pick's Theorem
                    int interior = interior_points(area, boundary);
                    
                    // Check if the number of interior points is a perfect square
                    if (is_square(interior)) {
                        ++count; // Increment count if it's a square number
                    }
                }
            }
        }
    }

    // Output the final count of quadrilaterals
    std::cout << count << std::endl;

    return 0;
}
