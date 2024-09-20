#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <future>

// A map that stores vectors of integers (grid rows) based on the sum of their digits.
std::map<int, std::vector<int>> gridRows;

// Function to calculate the sum of digits of a given number `n`
int sumDigits(int n){
    int sum = 0;
    while (n > 0){
        sum += n % 10;  // Add the last digit to the sum
        n /= 10;        // Remove the last digit
    }
    return sum;  // Return the total sum of digits
}

// Function to check if three rows form a valid set based on specific constraints
bool validSet(int row1, int row2, int row3){
    // Extracting digits from the 4-digit numbers row1, row2, and row3
    int a = row1 % 10;     // Last digit of row1
    int b = row2 % 10;     // Last digit of row2
    int c = row3 % 10;     // Last digit of row3
    int d = (row1 / 10) % 10;  // Second-to-last digit of row1
    int e = (row2 / 10) % 10;  // Second-to-last digit of row2
    int f = (row3 / 10) % 10;  // Second-to-last digit of row3
    int g = (row1 / 100) % 10; // Third-to-last digit of row1
    int h = (row2 / 100) % 10; // Third-to-last digit of row2
    int i = (row3 / 100) % 10; // Third-to-last digit of row3
    int j = (row1 / 1000) % 10; // First digit of row1
    int k = (row2 / 1000) % 10; // First digit of row2
    int l = (row3 / 1000) % 10; // First digit of row3

    // Calculate the sum of digits of the first row
    int s = sumDigits(row1);

    // Check if the combination of rows meets the specified conditions
    int w = s - a - b - c;
    if (w < 0 || w > 9)
        return false;

    int x = s - d - e - f;
    if (x < 0 || x > 9)
        return false;

    int y = s - g - h - i;
    if (y < 0 || y > 9)
        return false;

    int z = s - j - k - l;
    if (z < 0 || z > 9)
        return false;

    // Ensure the sum of all calculated values matches the sum of digits
    if (w + x + y + z != s)
        return false;

    // Additional checks to validate the set of rows
    if (a + e + i + z != s)
        return false;

    if (j + h + f + w != s)
        return false;

    // Return true if all conditions are satisfied
    return true;
}

// Function to count valid solutions for a given row1
int countSolutions(int row1){
    int count = 0;  // Counter for valid solutions
    int s = sumDigits(row1);  // Sum of digits of row1

    // Loop through all rows with the same digit sum as row1
    for (auto row2: gridRows[sumDigits(row1)]){

        // Perform early exits if the digit sums exceed `s`
        if (row2 % 10 + row1 % 10 > s)
            continue;
        if ((row2/10) % 10 + (row1/10) % 10 > s)
            continue;
        if ((row2/100) % 10 + (row1/100) % 10 > s)
            continue;
        if ((row2/1000) % 10 + (row1/1000) % 10 > s)
            break;
        if ((row2/10) % 10 + row1 % 10 > s)
            continue;        
        if ((row1/1000) % 10 + (row2/100) % 10 > s)
            continue;

        // Loop through all rows with the same digit sum for row3
        for (auto row3: gridRows[sumDigits(row1)]){

            // Check if the sum of digits in each column exceeds `s`
            if (row3 % 10 + row2 % 10 + row1 % 10 > s)
                continue;
            if ((row3/10) % 10 + (row2/10) % 10 + (row1/10) % 10 > s)
                continue;
            if ((row3/100) % 10 + (row2/100) % 10 + (row1/100) % 10 > s)
                continue;
            if ((row3/1000) % 10 + (row2/1000) % 10 + (row1/1000) % 10 > s)
                break;

            // Check if the three rows form a valid set
            if (validSet(row1, row2, row3))
                count++;  // Increment the solution count
        }
    }

    return count;  // Return the total count of valid solutions
}

int main(){
    unsigned long long count = 0;  // Total count of solutions

    // Populate the gridRows map with rows grouped by the sum of their digits
    for (int i=0; i<=9999; i++){
        if (gridRows.find(sumDigits(i)) == gridRows.end()){
            gridRows[sumDigits(i)] = std::vector<int>();
        }
        gridRows[sumDigits(i)].push_back(i);  // Add the row to the corresponding sum group
    }

    std::vector<std::future<unsigned long long>> futures;

    // Sort each vector of rows by the sum of digits and process them asynchronously
    for (auto it = gridRows.begin(); it != gridRows.end(); it++) {
        std::sort(it->second.begin(), it->second.end());
        futures.push_back(std::async(std::launch::async, [it]() {
            unsigned long long local_count = 0;
            for (int i = 0; i < it->second.size(); i++) {
                local_count += countSolutions(it->second[i]);  // Count valid solutions for each row
            }
            return local_count;  // Return the local solution count
        }));
    }

    // Accumulate the results from each async task
    for (auto& future : futures) {
        count += future.get();  // Add the result of each future to the total count
    }

    // Output the total count of valid solutions
    std::cout << count << std::endl;

    return 0;  // Program ends
}
