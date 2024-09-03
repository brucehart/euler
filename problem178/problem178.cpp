#include <iostream>
#include <unordered_map>

// Function to count the number of sequences based on the given conditions
unsigned long long count(int numDigits, unsigned int currentDigit, unsigned short pdMask)
{     
    // Cache to store already computed results for specific parameters
    static std::unordered_map<unsigned int, unsigned long long> cache;
    
    // Create a unique key for the cache based on the number of digits, current digit, and pdMask
    unsigned int countMask = (numDigits << 20) + (currentDigit << 16) + pdMask;

    unsigned long long totalCount = 0;

    // If currentDigit exceeds 9, return 0 as it is invalid
    if (currentDigit > 9)   
       return 0;    
    
    // Update the mask to include the current digit
    pdMask = pdMask | (1 << currentDigit);

    // Check if the result for the current state is already in the cache
    if (cache.find(countMask) != cache.end())
        return cache[countMask];

    // Base case: If numDigits is 1 and all digits have been used (pdMask is full)
    if (numDigits == 1 && pdMask == 0b1111111111)
    {
        cache[countMask] = 1; // Store the result in the cache
        return 1; // Return 1 because this is a valid sequence
    }
    // If numDigits is 1 but not all digits have been used, return 0
    else if (numDigits == 1)
    {
        cache[countMask] = 0; // Store the result in the cache
        return 0;
    }
    
    // Recursively count sequences by moving to the previous digit
    if (currentDigit > 0)    
        totalCount += count(numDigits - 1, currentDigit - 1, pdMask);       
    
    // Recursively count sequences by moving to the next digit
    if (currentDigit < 9)
        totalCount += count(numDigits - 1, currentDigit + 1, pdMask);        
            
    // Store the result in the cache before returning
    cache[countMask] = totalCount;
    return totalCount;
}

int main()
{
    int numDigits = 40; // Start with sequences of 40 digits
    unsigned long long totalCount = 0;

    // Decrement the number of digits until it reaches 9
    while (numDigits >= 9)
    {
        // Start from each digit from 1 to 9 as the first digit in the sequence
        for (int startDigit = 1; startDigit <= 9; startDigit++)
        {
            // Count all possible sequences starting with startDigit
            totalCount += count(numDigits, startDigit, 0);            
        }

        numDigits--; // Decrease the number of digits for the next iteration
    }

    // Output the total count of sequences
    std::cout << totalCount << std::endl;
    return 0;
}
