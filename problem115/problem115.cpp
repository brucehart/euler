#include <iostream>
#include <map>


// Cache to store previously computed results
std::map<int, unsigned long long> cache;

// Function to count the number of ways to fill a row of length n with blocks of minimum length m
unsigned long long count(int m, int n) // m = minimum length of red blocks, n = row length, count = F(m,n) combinations that row can be filled
{    
    // Base case: if the row length is 0, there is exactly one way to fill it (do nothing)
    if (n == 0) return 1;

    // Check if the result is already in the cache
    if (cache.find(n) != cache.end())
        return cache[n];
    
    // Start with the count of ways to fill the row by placing a single block of length 1
    auto c = count(m, n - 1);

    // Iterate over possible positions to place a block of at least length m
    while (m <= n)
    {
        auto remaining = n - m;

        // If there is space left after placing the block, reduce the remaining length by 1
        if (remaining > 0)
            remaining--;
        
        // Add the count of ways to fill the remaining part of the row
        c += count(m, remaining);
        m++;
    }

    // Store the computed result in the cache
    cache[n] = c;
    return c;
}

int main() {
    int n = 1, m = 50; // Initialize row length n and minimum block length m
    unsigned long long combos;
    unsigned long long limit = 1000000; // Limit for the number of combinations

    // Loop to find the smallest row length n for which the number of combinations exceeds the limit
    while(true)
    {
        combos = count(m, n);
        
        // Break the loop if the number of combinations exceeds the limit
        if(combos > limit)        
            break;        

        n++;
    }

    // Output the result
    std::cout << n << std::endl;

    return 0;
}