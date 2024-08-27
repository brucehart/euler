#include <iostream>
#include <vector>
#include <iomanip> // For setprecision
#include <cmath>

// Function to compute the nth term of the sequence using the generator function
long long generate_term(int n) {
    long long term = 1;
    long long power_n = n;
    
    // Calculate 1 - n + n^2 - n^3 + ... + n^10
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            term += power_n;
        } else {
            term -= power_n;
        }
        power_n *= n;  // Compute the next power of n
    }
    
    return term;
}

// Function to generate the sequence for the first k terms
std::vector<long long> generate_sequence(int k) {
    std::vector<long long> sequence(k);
    
    for (int n = 1; n <= k; ++n) {
        sequence[n-1] = generate_term(n);
    }
    
    return sequence;
}

// Function to invert a matrix
void invert_matrix(std::vector<std::vector<double>>& A) {
    int n = A.size();
    std::vector<std::vector<double>> I(n, std::vector<double>(n, 0));

    // Create an identity matrix I
    for (int i = 0; i < n; ++i) {
        I[i][i] = 1;
    }

    // Perform Gaussian elimination
    for (int i = 0; i < n; ++i) {
        double diag = A[i][i];
        for (int j = 0; j < n; ++j) {
            A[i][j] /= diag;
            I[i][j] /= diag;
        }
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; ++j) {
                    A[k][j] -= factor * A[i][j];
                    I[k][j] -= factor * I[i][j];
                }
            }
        }
    }

    // Copy the inverse matrix back into A
    A = I;
}

// Function to solve the system of linear equations to find coefficients
std::vector<double> solve_coefficients(const std::vector<int>& x_values, const std::vector<long long>& y_values) {
    int n = x_values.size();
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<double> b(n);

    // Set up the matrix A and vector b for Ax = b
    for (int i = 0; i < n; ++i) {
        double x_pow = 1;
        for (int j = 0; j < n; ++j) {
            A[i][j] = x_pow;
            x_pow *= x_values[i];
        }
        b[i] = y_values[i];
    }

    // Invert matrix A
    invert_matrix(A);

    // Multiply inverse(A) * b to get the coefficients
    std::vector<double> coefficients(n);
    for (int i = 0; i < n; ++i) {
        coefficients[i] = 0;
        for (int j = 0; j < n; ++j) {
            coefficients[i] += A[i][j] * b[j];
        }
    }

    return coefficients;
}

// Function to evaluate the polynomial at a given x
long long evaluate_polynomial(const std::vector<double>& coefficients, int x) {
    double result = 0;
    double x_pow = 1;

    for (const auto& coeff : coefficients) {
        result += coeff * x_pow;
        x_pow *= x;
    }

    return static_cast<long long>(std::round(result)); // Convert to integer
}

// Function to calculate the FITs and sum them up
long long calculate_FITs(const std::vector<long long>& sequence) {
    long long sum_FITs = 0;
    int k = sequence.size();

    for (int i = 1; i <= k; ++i) {  // Adjusted to include i = k
        std::vector<int> x_values(i);
        std::vector<long long> y_values(i);
        
        for (int j = 0; j < i; ++j) {
            x_values[j] = j + 1;
            y_values[j] = sequence[j];
        }

        // Solve for the polynomial coefficients using matrix inversion
        std::vector<double> coefficients = solve_coefficients(x_values, y_values);

        // Evaluate the polynomial at the next term (i + 1)
        long long predicted_value = evaluate_polynomial(coefficients, i + 1);

        if (predicted_value != sequence[i]) {
            sum_FITs += predicted_value;
        }
    }
    
    return sum_FITs;
}

int main() {
    int k = 10; // Number of terms you want to generate and consider for FITs
    std::vector<long long> sequence = generate_sequence(k);

    // Calculate the sum of FITs
    long long sum_FITs = calculate_FITs(sequence);

    // Print the result
    std::cout << sum_FITs << std::endl;

    return 0;
}
