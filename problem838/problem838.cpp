#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

// Define the upper limit
static int N = 1000000;

// Function to check if a number is prime using trial division
bool checkPrime(int n){
    if (n < 2) return false;
    for(int d = 2; d * d <= n; d++){
        if(n % d == 0)
            return false;
    }
    return true;
}

// Function to generate primes and populate unused_primes, used_primes, and toCheck
void generatePrimes(int n, std::set<int>& unused_primes, std::set<int>& used_primes, std::vector<int>& toCheck){
    for(int i = 2; i <= n; i++){
        bool is_prime = checkPrime(i);

        if(is_prime){
            if (i % 10 == 3)
                used_primes.insert(i);
            else            
                unused_primes.insert(i);               
        }

        // Add to toCheck if the number ends with 3 and is not prime
        if (i % 10 == 3 && !is_prime)
            toCheck.push_back(i);
    }    
}

int main(){
    std::set<int> unused_primes;
    std::set<int> used_primes;
    std::vector<int> toCheck;
    double logResult = 0.0;

    // Generate primes and populate the sets and vector
    generatePrimes(N, unused_primes, used_primes, toCheck);

    // Collection of sets where each set contains unused primes that divide a specific i in toCheck
    std::vector<std::set<int>> sets;

    for(int i : toCheck){
        std::set<int> divisors;
        bool primeFound = false;

        for (auto p: used_primes){
            if (p > i) break;

            if (i % p == 0){
                primeFound = true;
                break;
            }
        }

        if (primeFound) continue;

        for(auto p : unused_primes){
            if(p > i) break;

            if(i % p == 0){
                divisors.insert(p);
            }
        }
        if(!divisors.empty()){
            sets.push_back(divisors);
        }
    }

    // Sort the sets in descending order based on the smallest prime in each set
    std::sort(sets.begin(), sets.end(), [&](const std::set<int>& a, const std::set<int>& b) -> bool {
        if(a.empty() && b.empty()) return false;
        if(a.empty()) return false;
        if(b.empty()) return true;
        return *a.begin() > *b.begin();
    });

    // Process the sets
    while(!sets.empty()){
        // Ensure sets are sorted correctly after any modifications
        std::sort(sets.begin(), sets.end(), [&](const std::set<int>& a, const std::set<int>& b) -> bool {
            if(a.empty() && b.empty()) return false;
            if(a.empty()) return false;
            if(b.empty()) return true;
            return *a.begin() > *b.begin();
        });

        // Take the first set from the sorted list
        std::set<int> current_set = sets[0];
        if(current_set.empty()){
            // Remove empty sets and continue
            sets.erase(sets.begin());
            continue;
        }

        // Identify the smallest prime in the current set
        int smallest_prime = *current_set.begin();

        // Move the smallest prime from unused_primes to used_primes
        unused_primes.erase(smallest_prime);
        used_primes.insert(smallest_prime);

        // Remove the processed set from the collection
        sets.erase(sets.begin());

        // Remove any other sets that contain the newly added prime
        sets.erase(
            std::remove_if(sets.begin(), sets.end(),
                [&](const std::set<int>& s) -> bool {
                    return s.find(smallest_prime) != s.end();
                }),
            sets.end()
        );
    }

    // Compute the sum of natural logarithms of all used primes
    for(const auto& prime : used_primes){
        logResult += log(static_cast<double>(prime));
    }

    // Output the result with fixed precision
    std::cout << std::fixed << std::setprecision(6) << logResult << std::endl;

    return 0;
}
