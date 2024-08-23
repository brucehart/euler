#include <iostream>
#include <cmath>
#include <vector>

const double TARGET = -600000000000.0;
const int N = 5000;
const double EPSILON = 1e-12;

double compute_s(double r) {
    double s = 0.0;
    double r_power = 1.0; // Start with r^0
    for (int k = 1; k <= N; ++k) {
        s += (900.0 - 3.0 * k) * r_power;
        r_power *= r; // Multiply r_power by r for the next term
    }
    return s;
}

double compute_f(double r) {
    return compute_s(r) - TARGET;
}

double compute_f_prime(double r) {
    double f_prime = 0.0;
    double r_power = 1.0; // Start with r^0
    for (int k = 1; k <= N; ++k) {
        f_prime += (900.0 - 3.0 * k) * (k - 1) * r_power;
        r_power *= r; // Multiply r_power by r for the next term
    }
    return f_prime;
}

double compute_f_double_prime(double r) {
    double f_double_prime = 0.0;
    double r_power = 1.0; // Start with r^0
    for (int k = 2; k <= N; ++k) {
        f_double_prime += (900.0 - 3.0 * k) * (k - 1) * (k - 2) * r_power;
        r_power *= r; // Multiply r_power by r for the next term
    }
    return f_double_prime;
}

double halley_method(double r) {
    double delta;
    do {
        double f = compute_f(r);
        double f_prime = compute_f_prime(r);
        double f_double_prime = compute_f_double_prime(r);
        delta = (2.0 * f * f_prime) / (2.0 * pow(f_prime, 2) - f * f_double_prime);
        r -= delta;            
    } while (fabs(delta) > EPSILON);
    return r;
}

int main() {
    double r = 1.0; // Initial guess
    r = halley_method(r);
    std::cout.precision(13);
    std::cout << r << std::endl;
    return 0;
}

