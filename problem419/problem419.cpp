#include <iostream>
#include <vector>
#include <cstdint>

// Define types for convenience
typedef uint64_t ull;

// Custom Triplet structure
struct Triplet {
    int row, col;
    ull value;
    Triplet(int r, int c, ull v) : row(r), col(c), value(v) {}
};

// Sparse Matrix class using triplet representation
class SparseMat {
    int rows, cols;
    std::vector<Triplet> triplets;

public:
    SparseMat(int r, int c) : rows(r), cols(c) {}

    void addTriplet(int row, int col, ull value) {
        triplets.emplace_back(row, col, value);
    }

    std::vector<std::vector<ull>> toDense() const {
        std::vector<std::vector<ull>> dense(rows, std::vector<ull>(cols, 0));
        for (const auto& triplet : triplets) {
            dense[triplet.row][triplet.col] = triplet.value;
        }
        return dense;
    }

    int numRows() const { return rows; }
    int numCols() const { return cols; }
};

// Function to multiply two dense matrices with modulo
std::vector<std::vector<ull>> multiply_dense_mod(const std::vector<std::vector<ull>>& A,
                                                 const std::vector<std::vector<ull>>& B,
                                                 ull mod) {
    int n = A.size();
    std::vector<std::vector<ull>> C(n, std::vector<ull>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

// Function to multiply a dense matrix with a vector, applying modulo
std::vector<ull> multiply_dense_vector_mod(const std::vector<std::vector<ull>>& A,
                                           const std::vector<ull>& v,
                                           ull mod) {
    int n = A.size();
    std::vector<ull> result(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] = (result[i] + A[i][j] * v[j]) % mod;
        }
    }
    return result;
}

int main() {
    // Define the size of the matrix
    const int SIZE = 92;

    // Define the modulo as 2^30
    const ull MOD = 1ULL << 30; // 1073741824

    // Initialize the sparse matrix with triplets
    SparseMat M(SIZE, SIZE);

    // Populate the triplet list based on the updateSequence function
    //Reference table for look and say sequence: https://www.nathanieljohnston.com/2010/10/a-derivation-of-conways-degree-71-look-and-say-polynomial/
    // See also LookAndSay.csv  
    M.addTriplet(0, 28, 1);
    M.addTriplet(1, 31, 1);
    M.addTriplet(2, 29, 1);
    M.addTriplet(3, 30, 1);
    M.addTriplet(4, 32, 1);
    M.addTriplet(5, 53, 1);
    M.addTriplet(6, 36, 1);
    M.addTriplet(7, 37, 1);
    M.addTriplet(8, 38, 1);
    M.addTriplet(9, 39, 1);
    M.addTriplet(10, 43, 1);
    M.addTriplet(11, 45, 1);
    M.addTriplet(12, 46, 1);
    M.addTriplet(13, 47, 1);
    M.addTriplet(14, 48, 1);
    M.addTriplet(15, 50, 1);
    M.addTriplet(16, 51, 1);
    M.addTriplet(17, 49, 1);
    M.addTriplet(18, 44, 1);
    M.addTriplet(19, 52, 1);
    M.addTriplet(20, 40, 1);
    M.addTriplet(21, 41, 1);
    M.addTriplet(22, 42, 1);
    M.addTriplet(23, 34, 1);
    M.addTriplet(23, 35, 1);
    M.addTriplet(24, 56, 1);
    M.addTriplet(24, 57, 1);
    M.addTriplet(24, 58, 1);
    M.addTriplet(24, 59, 1);
    M.addTriplet(25, 54, 1);
    M.addTriplet(26, 55, 1);
    M.addTriplet(27, 33, 1);
    M.addTriplet(28, 15, 1);
    M.addTriplet(28, 16, 1);
    M.addTriplet(28, 18, 1);
    M.addTriplet(28, 31, 1);
    M.addTriplet(28, 34, 1);
    M.addTriplet(28, 35, 1);
    M.addTriplet(28, 53, 1);
    M.addTriplet(28, 56, 1);
    M.addTriplet(28, 57, 1);
    M.addTriplet(28, 58, 1);
    M.addTriplet(28, 59, 2); // Coefficient 2
    M.addTriplet(28, 81, 1);
    M.addTriplet(28, 85, 1);
    M.addTriplet(29, 17, 1);
    M.addTriplet(29, 86, 1);
    M.addTriplet(30, 87, 1);
    M.addTriplet(31, 19, 1);
    M.addTriplet(32, 34, 1);
    M.addTriplet(32, 35, 1);
    M.addTriplet(32, 61, 1);
    M.addTriplet(32, 81, 1);
    M.addTriplet(33, 88, 1);
    M.addTriplet(34, 90, 1);
    M.addTriplet(35, 89, 1);
    M.addTriplet(36, 91, 1);
    M.addTriplet(37, 66, 1);
    M.addTriplet(37, 74, 1);
    M.addTriplet(37, 85, 1);
    M.addTriplet(37, 86, 1);
    M.addTriplet(37, 87, 1);
    M.addTriplet(38, 66, 1);
    M.addTriplet(39, 62, 1);
    M.addTriplet(40, 63, 1);
    M.addTriplet(41, 64, 1);
    M.addTriplet(42, 65, 1);
    M.addTriplet(43, 67, 1);
    M.addTriplet(44, 82, 1);
    M.addTriplet(45, 83, 1);
    M.addTriplet(46, 74, 1);
    M.addTriplet(46, 75, 1);
    M.addTriplet(46, 76, 1);
    M.addTriplet(46, 77, 1);
    M.addTriplet(46, 78, 1);
    M.addTriplet(46, 79, 1);
    M.addTriplet(46, 80, 1);
    M.addTriplet(46, 81, 1);
    M.addTriplet(47, 68, 1);
    M.addTriplet(48, 70, 1);
    M.addTriplet(49, 71, 1);
    M.addTriplet(50, 72, 1);
    M.addTriplet(51, 73, 1);
    M.addTriplet(52, 84, 1);
    M.addTriplet(53, 69, 1);
    M.addTriplet(54, 6, 1);
    M.addTriplet(54, 75, 1);
    M.addTriplet(55, 76, 1);
    M.addTriplet(56, 77, 1);
    M.addTriplet(57, 78, 1);
    M.addTriplet(58, 79, 1);
    M.addTriplet(59, 80, 1);
    M.addTriplet(60, 31, 1);
    M.addTriplet(60, 34, 1);
    M.addTriplet(60, 35, 1);
    M.addTriplet(60, 53, 1);
    M.addTriplet(60, 59, 1);
    M.addTriplet(60, 60, 1);
    M.addTriplet(60, 81, 1);
    M.addTriplet(61, 1, 1);
    M.addTriplet(62, 0, 1);
    M.addTriplet(63, 1, 1);
    M.addTriplet(64, 2, 1);
    M.addTriplet(65, 3, 1);
    M.addTriplet(66, 57, 1);
    M.addTriplet(67, 4, 1);
    M.addTriplet(67, 59, 1);
    M.addTriplet(68, 5, 1);
    M.addTriplet(69, 7, 1);
    M.addTriplet(70, 8, 1);
    M.addTriplet(71, 20, 1);
    M.addTriplet(72, 21, 1);
    M.addTriplet(73, 22, 1);
    M.addTriplet(74, 18, 1);
    M.addTriplet(74, 19, 1);
    M.addTriplet(75, 9, 1);
    M.addTriplet(76, 10, 1);
    M.addTriplet(77, 12, 1);
    M.addTriplet(78, 13, 1);
    M.addTriplet(79, 14, 1);
    M.addTriplet(80, 15, 1);
    M.addTriplet(80, 16, 1);
    M.addTriplet(80, 17, 1);
    M.addTriplet(81, 11, 1);
    M.addTriplet(82, 23, 1);
    M.addTriplet(83, 6, 1);
    M.addTriplet(84, 31, 1);
    M.addTriplet(84, 58, 1);
    M.addTriplet(85, 24, 1);
    M.addTriplet(86, 25, 1);
    M.addTriplet(87, 26, 1);
    M.addTriplet(88, 27, 1);
    M.addTriplet(88, 59, 1);
    M.addTriplet(88, 85, 1);
    M.addTriplet(89, 16, 1);
    M.addTriplet(89, 35, 1);
    M.addTriplet(90, 15, 1);
    M.addTriplet(90, 34, 1);
    M.addTriplet(91, 18, 1);
    M.addTriplet(91, 27, 1);
    M.addTriplet(91, 53, 1);
    M.addTriplet(91, 56, 1);
    M.addTriplet(91, 81, 1);

    // Convert sparse matrix to dense
    std::vector<std::vector<ull>> denseM = M.toDense();

    // Initialize the 'prev' vector with all zeros
    std::vector<ull> prev(SIZE, 0);
    prev[23] = 1;
    prev[38] = 1;

    // Define the exponent N = 10^12 - 8
    const ull N = 1000000000000ULL - 8; // 999,999,999,992

    // Initialize M_power as M
    std::vector<std::vector<ull>> M_power = denseM;

    // Initialize the result vector as 'prev'
    std::vector<ull> result = prev;

    // Exponentiation by squaring
    ull exponent = N;

    while (exponent > 0) {
        if (exponent & 1ULL) {
            result = multiply_dense_vector_mod(M_power, result, MOD);
        }
        exponent >>= 1;
        if (exponent > 0) {
            M_power = multiply_dense_mod(M_power, M_power, MOD);
        }
    }

    //count the number of 1s, 2s, and 3s from each sequence in the reference table
    std::vector<unsigned int> A_n_coeffs = {3, 4, 6, 6, 3, 4, 7, 4, 5, 6, 6, 9, 7, 9, 11, 20, 20, 13, 8, 15, 7, 11, 11, 3, 3, 5, 5, 5, 1, 3, 3, 10, 1, 4, 14, 14, 4, 1, 3, 3, 5, 8, 8, 3, 6, 4, 3, 4, 5, 8, 13, 13, 10, 5, 3, 3, 5, 6, 10, 6, 0, 0, 2, 4, 6, 6, 3, 2, 4, 5, 6, 8, 13, 13, 4, 6, 6, 9, 10, 13, 11, 8, 3, 2, 6, 2, 4, 4, 1, 10, 10, 2};
    std::vector<unsigned int> B_n_coeffs = {1, 1, 4, 3, 0, 0, 4, 1, 2, 3, 2, 3, 3, 3, 4, 14, 13, 8, 3, 8, 6, 11, 10, 1, 3, 4, 3, 1, 1, 5, 4, 9, 0, 1, 12, 11, 3, 1, 1, 2, 4, 7, 6, 1, 2, 2, 2, 2, 5, 9, 17, 16, 6, 2, 3, 2, 3, 4, 7, 6, 2, 0, 1, 2, 6, 5, 3, 0, 0, 1, 2, 5, 10, 9, 3, 4, 3, 4, 5, 7, 8, 4, 1, 1, 6, 1, 3, 2, 1, 13, 14, 2};
    std::vector<unsigned int> C_n_coeffs = {0, 2, 2, 3, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 8, 9, 5, 3, 5, 1, 2, 3, 1, 1, 1, 2, 2, 0, 1, 2, 4, 1, 1, 6, 7, 1, 1, 1, 1, 1, 3, 4, 2, 2, 2, 2, 2, 2, 3, 4, 5, 4, 3, 1, 2, 3, 3, 4, 5, 0, 1, 1, 1, 2, 3, 1, 2, 2, 2, 2, 3, 5, 6, 2, 2, 3, 3, 3, 4, 4, 4, 2, 2, 3, 3, 3, 4, 1, 4, 3, 1};

    // Final computation of A_n, B_n, C_n
    unsigned long long A_n = 0;
    unsigned long long B_n = 0;
    unsigned long long C_n = 0;

    for (int i = 0; i < SIZE; ++i) {
        A_n += result[i] * A_n_coeffs[i];
        B_n += result[i] * B_n_coeffs[i];
        C_n += result[i] * C_n_coeffs[i];
    }

    // Apply modulo
    A_n %= MOD;
    B_n %= MOD;
    C_n %= MOD;

    // Output the result
    std::cout << A_n << "," << B_n << "," << C_n << std::endl;

    return 0;
}
