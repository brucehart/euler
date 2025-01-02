#include <bits/stdc++.h>

// Modulus for the last 9 digits
static const long long MOD = 1000000000LL;

// Dimension of our state vector = 18
static const int DIM = 18;

// Multiply two DIM x DIM matrices (mod MOD)
std::array<std::array<long long, DIM>, DIM> multiplyMatrix(
    const std::array<std::array<long long, DIM>, DIM>& A,
    const std::array<std::array<long long, DIM>, DIM>& B)
{
    std::array<std::array<long long, DIM>, DIM> C{};
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            __int128 temp = 0; // Use 128-bit intermediate to avoid overflow
            for(int k = 0; k < DIM; k++) {
                temp += (__int128)A[i][k] * B[k][j];
            }
            C[i][j] = (long long)(temp % MOD);
        }
    }
    return C;
}

// Exponentiate a DIM x DIM matrix by a positive integer exp (mod MOD).
std::array<std::array<long long, DIM>, DIM> powerMatrix(
    std::array<std::array<long long, DIM>, DIM> base,
    long long exp)
{
    // Initialize result as the identity matrix
    std::array<std::array<long long, DIM>, DIM> result{};
    for(int i = 0; i < DIM; i++) {
        result[i][i] = 1;
    }

    while(exp > 0) {
        if(exp & 1) {
            result = multiplyMatrix(result, base);
        }
        base = multiplyMatrix(base, base);
        exp >>= 1;
    }
    return result;
}

// Multiply a DIM x DIM matrix by a DIM x 1 vector (mod MOD).
std::array<long long, DIM> multiplyMatrixVector(
    const std::array<std::array<long long, DIM>, DIM>& M,
    const std::array<long long, DIM>& v)
{
    std::array<long long, DIM> w{};
    for(int i = 0; i < DIM; i++) {
        __int128 temp = 0; 
        for(int j = 0; j < DIM; j++) {
            temp += (__int128)M[i][j] * v[j];
        }
        w[i] = (long long)(temp % MOD);
    }
    return w;
}

int main()
{
    // Build the transition matrix M (18x18).
    // State vector V(n) = [ c(n), c(n-1), ..., c(n-8),
    //                       f(n), f(n-1), ..., f(n-8) ].
    //
    // Then V(n) = M * V(n-1).

    std::array<std::array<long long, DIM>, DIM> M{};
    
    // 1) The top-left 9x9 block updates c(n).
    //    c(n) = sum_{k=1..9} c(n-k) => sum_{j=0..8} c(n-1 - j).
    //    So row0 = (1,1,1,1,1,1,1,1,1) for columns c(n-1), c(n-2), ..., c(n-9).
    //    Then shifting c(n-1) -> c(n-2), etc. => below diagonal 1's.
    
    // row0 (to get c(n))
    for(int j = 0; j < 9; j++) {
        M[0][j] = 1; 
    }
    // rows 1..8: shift c(n-1) -> c(n-2), etc.
    // row1 = (1,0,0,0,0,0,0,0,0) but shifted by one column means M[1][0]=1
    for(int i = 1; i < 9; i++) {
        M[i][i - 1] = 1;
    }
    
    // 2) The bottom-left 9x9 block updates f(n).
    //    f(n) = 10*sum_{k=1..9} f(n-k) + sum_{k=1..9} k*c(n-k).
    //    The sum_{k=1..9} f(n-k) = f(n-1)+...+f(n-9) => columns 9..17 in V(n-1).
    //    The sum_{k=1..9} k*c(n-k) => columns 0..8 in V(n-1).

    // row9 = [coefficient of c(n-1)..c(n-9)] plus [coefficient of f(n-1)..f(n-9)].
    // c-part: (1,2,3,4,5,6,7,8,9)
    for(int j = 0; j < 9; j++) {
        M[9][j] = (j + 1); // j runs 0..8 => digit is (j+1)
    }
    // f-part: always multiplied by 10
    for(int j = 9; j < 18; j++) {
        M[9][j] = 10;
    }

    // Next rows 10..17 shift f(n-1)->f(n-2), etc.
    for(int i = 10; i < 18; i++) {
        M[i][i - 1] = 1;
    }

    // 3) The top-right and bottom-right 9x9 blocks remain 0
    //    because c(...) doesn't depend on old f(...), and f(...) doesn't
    //    shift "through" c(...) except in the row9 which we already handled.

    // Base vector V(0): c(0)=1, c(-k)=0, f(0)=0, f(-k)=0.
    std::array<long long, DIM> baseVector{};
    baseVector[0] = 1; // c(0)
    // The rest are zero by default.

    // We will compute sum of f(13^i) for i=1..17, all mod 1e9.
    long long answer = 0;

    // We'll iteratively build powers: E1 = M^13, E2 = E1^13, ...
    // For i from 1 to 17:
    //    V(13^i) = E_i * V(0).
    //    f(13^i) is the index 9 in that vector.

    // First, compute E1 = M^13.
    std::array<std::array<long long, DIM>, DIM> E = powerMatrix(M, 13);

    for(int i = 1; i <= 17; i++) {
        // Multiply E by baseVector => V(13^i).
        auto Vn = multiplyMatrixVector(E, baseVector);
        // f(13^i) is at index 9
        long long f_val = Vn[9] % MOD;
        answer = (answer + f_val) % MOD;

        // Now update E -> E^(13) for the next power
        if(i < 17) {
            E = powerMatrix(E, 13);
        }
    }

    // Print the result (last 9 digits)
    std::cout << answer << std::endl;
    return 0;
}

