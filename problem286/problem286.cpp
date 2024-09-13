#include <iostream>
#include <vector>
#include <cmath>

// Function to compute P(Total Points = target) given q
double computeProbability(double q, int target) {
    const int n = 50; // Number of shots
    std::vector<double> p(n + 1, 0.0); // Probabilities p_x
    std::vector<double> f(n + 1, 0.0); // PMF array

    // Calculate individual success probabilities p_x
    for (int x = 1; x <= n; ++x) {
        p[x] = 1.0 - (double)x / q;
    }

    // Initialize PMF array
    f[0] = 1.0;

    // Recursive computation
    for (int i = 1; i <= n; ++i) {
        for (int k = std::min(i, target); k >= 1; --k) {
            f[k] = f[k] * (1.0 - p[i]) + f[k - 1] * p[i];
        }
        f[0] *= (1.0 - p[i]);
    }

    // Return probability of scoring exactly 'target' points
    return f[target];
}

// Function to find q using the bisection method
double findQ(double lower, double upper, int target, double desiredProb, double tolerance) {
    const int maxIterations = 100;
    double mid = 0.0;

    for (int iter = 0; iter < maxIterations; ++iter) {
        mid = (lower + upper) / 2.0;
        double prob = computeProbability(mid, target);
        double diff = prob - desiredProb;

        if (std::abs(diff) < tolerance) {
            return mid;
        }

        if (diff > 0) {
            // Probability is too high, increase q
            lower = mid;
        } else {
            // Probability is too low, decrease q
            upper = mid;
        }
    }

    return mid; // Return the best estimate after maxIterations
}

int main() {
    double lower = 50.0;    // Since q > 50
    double upper = 100.0;   // An initial upper bound
    int target = 20;        // Target total points
    double desiredProb = 0.02;
    double tolerance = 1e-15;

    double q = findQ(lower, upper, target, desiredProb, tolerance);

    std::cout.precision(12);
    std::cout << q << std::endl;

    return 0;
}

