#include <iostream>
#include <vector>
#include <map>

int main() {
    // List of prime numbers used in the algorithm
    std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    // Map to store prime factor products and their corresponding powers
    std::map<unsigned long long, std::vector<int>> prime_powers;
    
    // Initialize the map with the key '1' and a vector of zeros (same size as the primes list)
    prime_powers[1] = std::vector<int>(primes.size(), 0);

    // Infinite loop until we find the desired solution
    while(true)
    {
        // Get the first element in the map (smallest key-value pair)
        auto next = prime_powers.begin();
        auto value = next->first;      // Extract the key (the product value)
        auto powers = next->second;    // Extract the powers vector for the corresponding primes
        prime_powers.erase(value);     // Remove the current entry from the map

        unsigned long long n = 1;
        
        // Calculate n as the product of (2*e + 1) for each power e in the 'powers' vector
        for (int e : powers) {
            n *= (2 * e + 1);
        }
        
        // After calculating n, increment it and divide by 2
        n++;
        n /= 2;

        // Check if n exceeds 4 million
        if (n > 4000000) {
            // If n exceeds 4 million, print the current value and exit the program
            std::cout << value << std::endl;
            return 0;
        }
        
        // Generate new values by incrementing the powers of the prime factors
        for (int i = 0; i < powers.size(); i++)
        {                  
            // Break the loop if a prime power exceeds certain constraints (e.g., i > 3)
            if (powers[i] > 0 && i > 3)
                break;
            
            // Increment the power of the current prime
            powers[i]++;                        
            // Multiply the current value by the corresponding prime to generate a new product
            value *= primes[i];
            // Store the new value and powers vector in the map
            prime_powers[value] = powers;
        }       
    }

    return 0;
}
