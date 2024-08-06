#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Function to convert vector of integers to a concatenated string
string vectorToString(const vector<int>& vec) {
    string result;
    for (int num : vec) {
        result += to_string(num);
    }
    return result;
}

// Function to check if the given permutation forms a valid "magic" 5-gon ring
bool isValidRing(const vector<int>& perm, int& total, vector<vector<int>>& groups) {
    total = perm[0] + perm[5] + perm[6];
    groups[0] = {perm[0], perm[5], perm[6]};
    
    for (int i = 1; i < 5; ++i) {
        int group_total = perm[i] + perm[i+5] + perm[(i+1)%5+5];
        if (group_total != total) {
            return false;
        }
        groups[i] = {perm[i], perm[i+5], perm[(i+1)%5+5]};
    }
    
    return true;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    string maxString;
    
    do {
        vector<vector<int>> groups(5);
        int total;
        if (isValidRing(nums, total, groups)) {
            string currentString;
            int start = min_element(groups.begin(), groups.end()) - groups.begin();
            for (int i = 0; i < 5; ++i) {
                int index = (start + i) % 5;
                currentString += vectorToString(groups[index]);
            }
            if (currentString.length() == 16 && currentString > maxString) {
                maxString = currentString;
            }
        }
    } while (next_permutation(nums.begin(), nums.end()));
    
    cout << maxString << endl;
    
    return 0;
}
