#include <iostream>// Function to compute T(S)

long long computeT(int S) {
    long long S_cubed = static_cast<long long>(S) * S * S;
    long long S_squared = static_cast<long long>(S) * S;
    
    long long term1 = 1678 * S_cubed;
    long long term2 = 3117 * S_squared;
    long long term3 = 88 * S;
    long long term4 = 345 * (S % 2);
    long long term5 = 320 * (S % 3);
    long long term6 = 90 * (S % 4);
    
    long long mod_5_term = S_cubed - S_squared + S;
    long long term7 = 288 * (mod_5_term % 5);
    
    // Compute T(S)
    long long T = (term1 + term2 + term3 - term4 - term5 - term6 - term7) / 240;

    return T;
}

int main(){
    int S = 36;
    long long result = computeT(S);
    std::cout << result << std::endl;
    return 0;
}
