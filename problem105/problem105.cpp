#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <sstream>
#include <fstream>

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


int main(){
    std::ifstream file("0105_sets.txt");
    std::string line;
    int totalSum = 0;

    while (std::getline(file, line)) {
        std::vector<int> set;
        std::stringstream ss(line);
        std::string number;

        while (std::getline(ss, number, ',')) {
            set.push_back(std::stoi(number));
        }

        if (isSpecialSumSet(set)) {
            totalSum += std::accumulate(set.begin(), set.end(), 0);
        }
    }

    std::cout << totalSum << std::endl;
    return 0;
}