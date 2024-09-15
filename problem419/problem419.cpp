#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <cstdint>

// Define types for convenience
typedef uint64_t ull;
typedef Eigen::Triplet<ull> Triplet;
typedef Eigen::SparseMatrix<ull> SparseMat;
typedef Eigen::Matrix<ull, Eigen::Dynamic, 1> Vector;

// Function to apply modulo to a Sparse Matrix
SparseMat multiply_sparse_mod(const SparseMat& A, const SparseMat& B, const ull mod) {
    // Convert SparseMat to Dense for multiplication
    Eigen::Matrix<ull, Eigen::Dynamic, Eigen::Dynamic> denseA = Eigen::Matrix<ull, Eigen::Dynamic, Eigen::Dynamic>(A);
    Eigen::Matrix<ull, Eigen::Dynamic, Eigen::Dynamic> denseB = Eigen::Matrix<ull, Eigen::Dynamic, Eigen::Dynamic>(B);
    
    // Multiply the dense matrices
    Eigen::Matrix<ull, Eigen::Dynamic, Eigen::Dynamic> denseC = denseA * denseB;
    
    // Apply modulo to each element
    denseC = denseC.unaryExpr([mod](ull x) -> ull { return x % mod; });
    
    // Convert back to SparseMat
    SparseMat C = denseC.sparseView();
    C.makeCompressed();
    return C;
}

// Function to multiply a Sparse Matrix with a Vector, applying modulo
Vector multiply_sparse_vector_mod(const SparseMat& A, const Vector& v, const ull mod) {
    // Convert SparseMat to Dense for multiplication
    Eigen::Matrix<ull, Eigen::Dynamic, Eigen::Dynamic> denseA = Eigen::Matrix<ull, Eigen::Dynamic, Eigen::Dynamic>(A);
    
    // Multiply the dense matrix with the vector
    Eigen::Matrix<ull, Eigen::Dynamic, 1> denseResult = denseA * v;
    
    // Apply modulo to each element
    denseResult = denseResult.unaryExpr([mod](ull x) -> ull { return x % mod; });
    
    return denseResult;
}

int main() {
    // Define the size of the matrix
    const int SIZE = 92;
    
    // Define the modulo as 2^30
    const ull MOD = 1ULL << 30; // 1073741824
    
    // Initialize a list to hold non-zero entries as Triplets
    std::vector<Triplet> tripletList;
    
    // Populate the triplet list based on the updateSequence function
    //Reference table for look and say sequence: https://www.nathanieljohnston.com/2010/10/a-derivation-of-conways-degree-71-look-and-say-polynomial/
    // See also LookAndSay.csv  
    tripletList.emplace_back(0, 28, 1);
    tripletList.emplace_back(1, 31, 1);
    tripletList.emplace_back(2, 29, 1);
    tripletList.emplace_back(3, 30, 1);
    tripletList.emplace_back(4, 32, 1);
    tripletList.emplace_back(5, 53, 1);
    tripletList.emplace_back(6, 36, 1);
    tripletList.emplace_back(7, 37, 1);
    tripletList.emplace_back(8, 38, 1);
    tripletList.emplace_back(9, 39, 1);
    tripletList.emplace_back(10, 43, 1);
    tripletList.emplace_back(11, 45, 1);
    tripletList.emplace_back(12, 46, 1);
    tripletList.emplace_back(13, 47, 1);
    tripletList.emplace_back(14, 48, 1);
    tripletList.emplace_back(15, 50, 1);
    tripletList.emplace_back(16, 51, 1);
    tripletList.emplace_back(17, 49, 1);
    tripletList.emplace_back(18, 44, 1);
    tripletList.emplace_back(19, 52, 1);
    tripletList.emplace_back(20, 40, 1);
    tripletList.emplace_back(21, 41, 1);
    tripletList.emplace_back(22, 42, 1);
    tripletList.emplace_back(23, 34, 1);
    tripletList.emplace_back(23, 35, 1);
    tripletList.emplace_back(24, 56, 1);
    tripletList.emplace_back(24, 57, 1);
    tripletList.emplace_back(24, 58, 1);
    tripletList.emplace_back(24, 59, 1);
    tripletList.emplace_back(25, 54, 1);
    tripletList.emplace_back(26, 55, 1);
    tripletList.emplace_back(27, 33, 1);
    tripletList.emplace_back(28, 15, 1);
    tripletList.emplace_back(28, 16, 1);
    tripletList.emplace_back(28, 18, 1);
    tripletList.emplace_back(28, 31, 1);
    tripletList.emplace_back(28, 34, 1);
    tripletList.emplace_back(28, 35, 1);
    tripletList.emplace_back(28, 53, 1);
    tripletList.emplace_back(28, 56, 1);
    tripletList.emplace_back(28, 57, 1);
    tripletList.emplace_back(28, 58, 1);
    tripletList.emplace_back(28, 59, 2); // Coefficient 2
    tripletList.emplace_back(28, 81, 1);
    tripletList.emplace_back(28, 85, 1);
    tripletList.emplace_back(29, 17, 1);
    tripletList.emplace_back(29, 86, 1);
    tripletList.emplace_back(30, 87, 1);
    tripletList.emplace_back(31, 19, 1);
    tripletList.emplace_back(32, 34, 1);
    tripletList.emplace_back(32, 35, 1);
    tripletList.emplace_back(32, 61, 1);
    tripletList.emplace_back(32, 81, 1);
    tripletList.emplace_back(33, 88, 1);
    tripletList.emplace_back(34, 90, 1);
    tripletList.emplace_back(35, 89, 1);
    tripletList.emplace_back(36, 91, 1);
    tripletList.emplace_back(37, 66, 1);
    tripletList.emplace_back(37, 74, 1);
    tripletList.emplace_back(37, 85, 1);
    tripletList.emplace_back(37, 86, 1);
    tripletList.emplace_back(37, 87, 1);
    tripletList.emplace_back(38, 66, 1);
    tripletList.emplace_back(39, 62, 1);
    tripletList.emplace_back(40, 63, 1);
    tripletList.emplace_back(41, 64, 1);
    tripletList.emplace_back(42, 65, 1);
    tripletList.emplace_back(43, 67, 1);
    tripletList.emplace_back(44, 82, 1);
    tripletList.emplace_back(45, 83, 1);
    tripletList.emplace_back(46, 74, 1);
    tripletList.emplace_back(46, 75, 1);
    tripletList.emplace_back(46, 76, 1);
    tripletList.emplace_back(46, 77, 1);
    tripletList.emplace_back(46, 78, 1);
    tripletList.emplace_back(46, 79, 1);
    tripletList.emplace_back(46, 80, 1);
    tripletList.emplace_back(46, 81, 1);
    tripletList.emplace_back(47, 68, 1);
    tripletList.emplace_back(48, 70, 1);
    tripletList.emplace_back(49, 71, 1);
    tripletList.emplace_back(50, 72, 1);
    tripletList.emplace_back(51, 73, 1);
    tripletList.emplace_back(52, 84, 1);
    tripletList.emplace_back(53, 69, 1);
    tripletList.emplace_back(54, 6, 1);
    tripletList.emplace_back(54, 75, 1);
    tripletList.emplace_back(55, 76, 1);
    tripletList.emplace_back(56, 77, 1);
    tripletList.emplace_back(57, 78, 1);
    tripletList.emplace_back(58, 79, 1);
    tripletList.emplace_back(59, 80, 1);
    tripletList.emplace_back(60, 31, 1);
    tripletList.emplace_back(60, 34, 1);
    tripletList.emplace_back(60, 35, 1);
    tripletList.emplace_back(60, 53, 1);
    tripletList.emplace_back(60, 59, 1);
    tripletList.emplace_back(60, 60, 1);
    tripletList.emplace_back(60, 81, 1);
    tripletList.emplace_back(61, 1, 1);
    tripletList.emplace_back(62, 0, 1);
    tripletList.emplace_back(63, 1, 1);
    tripletList.emplace_back(64, 2, 1);
    tripletList.emplace_back(65, 3, 1);
    tripletList.emplace_back(66, 57, 1);
    tripletList.emplace_back(67, 4, 1);
    tripletList.emplace_back(67, 59, 1);
    tripletList.emplace_back(68, 5, 1);
    tripletList.emplace_back(69, 7, 1);
    tripletList.emplace_back(70, 8, 1);
    tripletList.emplace_back(71, 20, 1);
    tripletList.emplace_back(72, 21, 1);
    tripletList.emplace_back(73, 22, 1);
    tripletList.emplace_back(74, 18, 1);
    tripletList.emplace_back(74, 19, 1);
    tripletList.emplace_back(75, 9, 1);
    tripletList.emplace_back(76, 10, 1);
    tripletList.emplace_back(77, 12, 1);
    tripletList.emplace_back(78, 13, 1);
    tripletList.emplace_back(79, 14, 1);
    tripletList.emplace_back(80, 15, 1);
    tripletList.emplace_back(80, 16, 1);
    tripletList.emplace_back(80, 17, 1);
    tripletList.emplace_back(81, 11, 1);
    tripletList.emplace_back(82, 23, 1);
    tripletList.emplace_back(83, 6, 1);
    tripletList.emplace_back(84, 31, 1);
    tripletList.emplace_back(84, 58, 1);
    tripletList.emplace_back(85, 24, 1);
    tripletList.emplace_back(86, 25, 1);
    tripletList.emplace_back(87, 26, 1);
    tripletList.emplace_back(88, 27, 1);
    tripletList.emplace_back(88, 59, 1);
    tripletList.emplace_back(88, 85, 1);
    tripletList.emplace_back(89, 16, 1);
    tripletList.emplace_back(89, 35, 1);
    tripletList.emplace_back(90, 15, 1);
    tripletList.emplace_back(90, 34, 1);
    tripletList.emplace_back(91, 18, 1);
    tripletList.emplace_back(91, 27, 1);
    tripletList.emplace_back(91, 53, 1);
    tripletList.emplace_back(91, 56, 1);
    tripletList.emplace_back(91, 81, 1);
    
    // Create the sparse matrix and populate it with the triplet list
    SparseMat M(SIZE, SIZE);
    M.setFromTriplets(tripletList.begin(), tripletList.end());
    
    // Compress the matrix for efficient arithmetic operations
    M.makeCompressed();
    
    // Display the number of non-zero entries
    //std::cout << "Number of non-zero entries in M: " << M.nonZeros() << std::endl;
    
    // Initialize the 'prev' vector with all zeros
    Vector prev(SIZE);
    prev.setZero();

    prev(23) = 1;
    prev(38) = 1;
        
    // Define the exponent N = 10^12 - 8
    const ull N = 1000000000000ULL - 8; // 999,999,999,992
    
    // Initialize M_power as M
    SparseMat M_power = M;
    
    // Initialize the result vector as 'prev'
    Vector result = prev;
    
    // Initialize a temporary vector for intermediate multiplications
    Vector temp(SIZE);
    temp.setZero();
    
    // Exponentiation by squaring
    //std::cout << "Starting matrix exponentiation by squaring for N = " << N << "..." << std::endl;
    
    ull exponent = N;
    
    while (exponent > 0) {
        if (exponent & 1ULL) {
            // Multiply M_power with result vector, applying modulo
            result = multiply_sparse_vector_mod(M_power, result, MOD);
        }
        exponent >>= 1;
        if (exponent > 0) {
            // Square M_power, applying modulo
            M_power = multiply_sparse_mod(M_power, M_power, MOD);
        }
    }
    
    //std::cout << "Matrix exponentiation completed." << std::endl;
    
    // Print the resulting vector
    //std::cout << "Final state vector after " << (1000000000000ULL - 8) << " iterations (mod 2^30):" << std::endl;

    //count the number of 1s, 2s, and 3s from each sequence in the reference table
    std::vector<unsigned int> A_n_coeffs = {3, 4, 6, 6, 3, 4, 7, 4, 5, 6, 6, 9, 7, 9, 11, 20, 20, 13, 8, 15, 7, 11, 11, 3, 3, 5, 5, 5, 1, 3, 3, 10, 1, 4, 14, 14, 4, 1, 3, 3, 5, 8, 8, 3, 6, 4, 3, 4, 5, 8, 13, 13, 10, 5, 3, 3, 5, 6, 10, 6, 0, 0, 2, 4, 6, 6, 3, 2, 4, 5, 6, 8, 13, 13, 4, 6, 6, 9, 10, 13, 11, 8, 3, 2, 6, 2, 4, 4, 1, 10, 10, 2};
    std::vector<unsigned int> B_n_coeffs = {1, 1, 4, 3, 0, 0, 4, 1, 2, 3, 2, 3, 3, 3, 4, 14, 13, 8, 3, 8, 6, 11, 10, 1, 3, 4, 3, 1, 1, 5, 4, 9, 0, 1, 12, 11, 3, 1, 1, 2, 4, 7, 6, 1, 2, 2, 2, 2, 5, 9, 17, 16, 6, 2, 3, 2, 3, 4, 7, 6, 2, 0, 1, 2, 6, 5, 3, 0, 0, 1, 2, 5, 10, 9, 3, 4, 3, 4, 5, 7, 8, 4, 1, 1, 6, 1, 3, 2, 1, 13, 14, 2};
    std::vector<unsigned int> C_n_coeffs = {0, 2, 2, 3, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 8, 9, 5, 3, 5, 1, 2, 3, 1, 1, 1, 2, 2, 0, 1, 2, 4, 1, 1, 6, 7, 1, 1, 1, 1, 1, 3, 4, 2, 2, 2, 2, 2, 2, 3, 4, 5, 4, 3, 1, 2, 3, 3, 4, 5, 0, 1, 1, 1, 2, 3, 1, 2, 2, 2, 2, 3, 5, 6, 2, 2, 3, 3, 3, 4, 4, 4, 2, 2, 3, 3, 3, 4, 1, 4, 3, 1};

    unsigned long long A_n = 0;
    unsigned long long B_n = 0;
    unsigned long long C_n = 0;

    for(int i = 0; i < SIZE; ++i) {
        //std::cout << "Index " << i << ": " << result(i) << std::endl;
        A_n += result(i) * A_n_coeffs[i];
        B_n += result(i) * B_n_coeffs[i];
        C_n += result(i) * C_n_coeffs[i];
    }

    // Apply modulo to A_n, B_n, and C_n
    A_n %= MOD;
    B_n %= MOD;
    C_n %= MOD;

    // std::cout << "A_n: " << A_n << std::endl;
    // std::cout << "B_n: " << B_n << std::endl;
    // std::cout << "C_n: " << C_n << std::endl;

    std::cout << A_n << "," << B_n << "," << C_n << std::endl;

    





    
    return 0;
}
