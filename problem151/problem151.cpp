#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Function to calculate the probability based on the 'sheets' vector
// 'sheets' represents the distribution of sheets, where each element is
// the number of sheets at a certain position
double calcProb(std::vector<int> sheets)
{
    double oneSheet = 0; // Variable to store the probability result
    int numSheets = std::accumulate(sheets.begin(), sheets.end(), 0); // Sum up all the sheets to get the total number of sheets

    // If there is exactly one sheet in the last position, return 0 probability
    if (sheets[4] == 1 && numSheets == 1)    
        return 0;
    // If the first sheet is not 1 and there is exactly one sheet in total, set oneSheet to 1
    else if (sheets[0] != 1 && numSheets == 1) 
        oneSheet = 1;
    
    // Iterate through each position in the 'sheets' vector
    for (auto i = 0; i < sheets.size(); i++)
    {
        auto newSheets = sheets; // Make a copy of the current sheet distribution

        if (sheets[i] == 0) continue; // Skip if no sheet exists at this position
        newSheets[i]--; // Remove one sheet from the current position
        
        // Redistribute the sheets from the current position to the next positions
        for(auto j = i+1; j < newSheets.size(); j++)
            newSheets[j]++;
        
        // Calculate the probability of picking a sheet from position 'i'
        double prob = (double)sheets[i] / numSheets;
        // Recursively calculate the probability for the new sheet distribution
        oneSheet += prob * calcProb(newSheets);
    }

    // Return the computed probability
    return oneSheet;
}

int main(){
    // Initial vector representing the distribution of sheets, with one sheet at the first position
    std::vector<int> sheets = {1,0,0,0,0};
    // Calculate and print the probability based on the initial distribution
    std::cout << calcProb(sheets) << std::endl;
    return 0;
}
