#include <iostream>
#include <vector>

// Function to calculate the sum of elements in vector A
int sum(std::vector<int> &A) {
    int sum = 0;
    // Iterate over the vector and accumulate the sum of all elements
    for (int i = 0; i < A.size(); i++) {
        sum += A[i];
    }
    return sum;
}

// Function to check if a set A is a special sum set
bool isSpecialSumSet(std::vector<int> &A) {
    int n = A.size();
    
    // Check all possible subsets using bit manipulation
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = i + 1; j < (1 << n); ++j) {
            std::vector<int> B, C;   // Subsets B and C
            int sumB = 0, sumC = 0;  // Sum of subsets B and C
            
            // Create subsets B and C from A based on bitmasking
            for (int k = 0; k < n; ++k) {
                if (i & (1 << k)) {  // If bit k is set in subset i, add A[k] to B
                    B.push_back(A[k]);
                    sumB += A[k];
                }
                if (j & (1 << k)) {  // If bit k is set in subset j, add A[k] to C
                    C.push_back(A[k]);
                    sumC += A[k];
                }
            }
            
            // If the sums of two subsets are equal, A is not a special sum set
            if (sumB == sumC) {
                return false;
            }
            
            // If B has more elements but a smaller or equal sum, it's invalid
            if (B.size() > C.size() && sumB <= sumC) {
                return false;
            }
            
            // If C has more elements but a smaller or equal sum, it's invalid
            if (C.size() > B.size() && sumC <= sumB) {
                return false;
            }
        }
    }
    
    // If no invalid conditions are found, A is a special sum set
    return true;
}

// Function to create a string representation of the sum set
std::string bestSumString(std::vector<int>& A) {
    std::string result = "";
    // Concatenate all elements of A into a string
    for (int i = 0; i < A.size(); ++i) {
        result += std::to_string(A[i]);
    }
    return result;
}

int main() {
    int bestSum;  // Variable to store the best sum found
    std::vector<int> bestA;  // Vector to store the best set of numbers
    
    std::vector<int> A6 = {11, 18, 19, 20, 22, 25};  // Initial set of numbers
    int b = 20;  // A base number to add to each element in A6
    std::vector<int> A7 = {b};  // Initialize A7 with the base number
    
    // Add each element in A6 to A7 after adding the base number
    for (auto x : A6)
        A7.push_back(x + b);

    // Check if A7 is a special sum set, and if so, initialize the best sum and best set
    if (isSpecialSumSet(A7)) {
        bestSum = sum(A7);
        bestA = A7;
    }
    
    // Try improving the sum by decrementing one element at a time
    for (int i = 0; i < A7.size(); i++) {
        auto trialA = A7;
        trialA[i] -= 1;  // Decrement one element of A7
        
        // If the new sum is better and it's still a special sum set, update the best values
        if (sum(trialA) < bestSum && isSpecialSumSet(trialA)) {
            bestSum = sum(trialA);
            bestA = trialA;
            std::cout << "New best sum" << std::endl;
        }
    }

    // Try adjusting A7 by adding 1 to one element and subtracting 1 from two other elements
    for (int i = 0; i < A7.size(); i++) {
        for (int j = 0; j < A7.size(); j++) {
            if (j == i) continue;  // Skip if i and j are the same
            for (int k = j + 1; k < A7.size(); k++) {
                if (k == i) continue;  // Skip if i and k are the same
                
                auto trialA = A7;
                trialA[i] += 1;  // Increment one element
                trialA[j] -= 1;  // Decrement two other elements
                trialA[k] -= 1;
                
                // If the new sum is better and it's still a special sum set, update the best values
                if (sum(trialA) < bestSum && isSpecialSumSet(trialA)) {
                    bestSum = sum(trialA);
                    bestA = trialA;
                    std::cout << "New best sum: " << bestSum << std::endl;
                }
            }
        }
    }

    // Output the string representation of the best set found
    std::cout << bestSumString(bestA) << std::endl;

    return 0;
}
