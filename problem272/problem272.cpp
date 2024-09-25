#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

using boost::multiprecision::cpp_int;

std::set<uint64_t> specialPrimes;
static const uint64_t N_MAX = 100000000000;
static const uint64_t BLOCK_SIZE = 3*7*13*19*31*37*43;

// Basic primality test for small numbers
bool isPrime(int64_t n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to create the set of special primes
void createSpecialPrimes(){
    uint64_t maxPrime = N_MAX / (3* 7 * 13 * 19);
    specialPrimes.insert(3);
    for(uint64_t i = 5; i <= maxPrime; i++){
        if (isPrime(i) && i % 3 == 1){
            specialPrimes.insert(i);
        }
    }
}

int main(){
    createSpecialPrimes();  
    uint64_t startCount = 0;
    cpp_int sum = 0;
    cpp_int initialSum = 0;

    // Define initialPrimes and compute largePrimes
    std::set<uint64_t> initialPrimes = {3, 7, 13, 19, 31, 37, 43};
    std::set<uint64_t> largePrimes;

    // Remove initialPrimes from specialPrimes to get largePrimes
    std::set_difference(specialPrimes.begin(), specialPrimes.end(),
                        initialPrimes.begin(), initialPrimes.end(),
                        std::inserter(largePrimes, largePrimes.begin()));

    // Precompute initialSet for a full block
    std::vector<uint32_t> initialSet(BLOCK_SIZE, 0);
    std::vector<uint32_t> primeCount(BLOCK_SIZE, 0);

    for (auto prime : initialPrimes){
        uint64_t n = prime;
        while (n < BLOCK_SIZE){
            initialSet[n]++;
            if (initialSet[n] == 5){
                sum += n;
            }
            else if (initialSet[n] == 6){
                sum -= n;
            }
            n += prime;
        }
    }

    initialSum = sum;

    // Main loop to process each block
    while (startCount < N_MAX){
        // Determine the size of the current block
        uint64_t currentBlockSize = std::min(BLOCK_SIZE, N_MAX - startCount);
        
        for (uint64_t n = 0; n < currentBlockSize; ++n) {
            if (initialSet[n] == 5) {
                sum += n + startCount;
            }
        }
                
        std::copy(initialSet.begin(), initialSet.begin() + currentBlockSize, primeCount.begin());

        // Process largePrimes within the current block
        for (auto prime : largePrimes){
            // Find the first multiple of prime within the current block
            uint64_t firstMultiple = (startCount / prime) * prime;
            if (firstMultiple < startCount){
                firstMultiple += prime;
            }

            // Iterate over multiples of prime within the block
            for(uint64_t n = firstMultiple; n < startCount + currentBlockSize; n += prime){
                
                if(n < startCount){
                    continue;
                }
                
                uint64_t index = n - startCount;
                
                if(index >= currentBlockSize){
                    break; // Prevent out-of-bounds
                }              
                
                primeCount[index]++;

                if (primeCount[index] == 5){
                    sum += n;
                }
                else if (primeCount[index] == 6){
                    sum -= n;
                }
            }
        }

        // Advance to the next block
        startCount += BLOCK_SIZE;
        std::streamsize ss = std::cout.precision();
        std::cout << startCount << " (" << std::fixed << std::setprecision(2) << (static_cast<double>(startCount) / N_MAX) * 100 << "%) : " << sum << std::endl;
        std::cout.precision(ss);
    }

    std::cout << "Total Sum: " << sum << std::endl;
    
    return 0;
}
