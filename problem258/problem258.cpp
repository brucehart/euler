#include <iostream>
#include <vector>

// Type alias for convenience
using ll = long long;

// Modulo constant
constexpr ll MOD = 20092010;

// Represents a matrix as a 1D vector in row-major order
using Matrix = std::vector<ll>;

// Function to multiply two matrices (A * B) modulo MOD
Matrix multiply(const Matrix& A, const Matrix& B, int size) {
    Matrix C(size * size, 0);
    for(int i = 0; i < size; ++i){
        for(int k = 0; k < size; ++k){
            ll a_ik = A[i * size + k];
            if(a_ik == 0) continue;
            for(int j = 0; j < size; ++j){
                C[i * size + j] = (C[i * size + j] + a_ik * B[k * size + j]) % MOD;
            }
        }
    }
    return C;
}

// Function to perform matrix exponentiation (A ^ power) modulo MOD
Matrix matrix_pow(Matrix A, ll power, int size) {
    // Initialize result as identity matrix
    Matrix result(size * size, 0);
    for(int i = 0; i < size; ++i){
        result[i * size + i] = 1;
    }
    while(power > 0){
        if(power & 1){
            result = multiply(result, A, size);
        }
        A = multiply(A, A, size);
        power >>= 1;
        //std::cout << power << std::endl;
    }
    return result;
}

int main(){
    // Optimize I/O operations
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    // Parameters
    ll k = 1000000000000000000; // 10^18
    ll m = MOD;
    
    // Order of the recurrence
    const int order = 2000;
    
    // Initial state vector: g_0 to g_1999 = 1
    std::vector<ll> initial(order, 1);
    
    // Transition matrix as a 1D vector
    Matrix T(order * order, 0);
    
    // Set T[0][1998] and T[0][1999] to 1
    T[0 * order + 1998] = 1;
    T[0 * order + 1999] = 1;
    
    // Set the sub-diagonal elements to 1 for state shifting
    for(int i = 1; i < order; ++i){
        T[i * order + (i - 1)] = 1;
    }
    
    // Calculate the exponent for matrix exponentiation
    ll exponent = k - (order - 1);
    
    // Handle the edge case where k is less than the order
    if(k < order){
        std::cout << 1;
        return 0;
    }
    
    // Compute T^exponent
    Matrix T_exp = matrix_pow(T, exponent, order);
    
    // Compute the final result by summing the first row of T_exp
    ll result = 0;
    for(int j = 0; j < order; ++j){
        result = (result + T_exp[j]) % m;
    }
    
    // Output the result
    std::cout << result << std::endl;
    
    return 0;
}

