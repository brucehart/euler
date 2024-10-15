#include <iostream>
#include <vector>
#include <cstdint>
#include <iomanip> // For std::setw if needed

// Define the maximum exponent for 2^i
const long MAX_EXPONENT = 31;

// Bitmask array to track row flips
std::vector<uint32_t> rowFlipMask;

// Inline function to retrieve the state of a specific bit
inline bool getBit(const std::vector<uint32_t>& mask, long index) {
    return (mask[index >> 5] >> (index & 31)) & 1;
}

// Inline function to set a specific bit
inline void setBit(std::vector<uint32_t>& mask, long index) {
    mask[index >> 5] |= (1u << (index & 31));
}

// Function to compute the minimal number of flips T(N) for a given board size N
long computeMinimalFlips(long boardSize) {
    // Initialize the row flip mask to 0
    std::fill(rowFlipMask.begin(), rowFlipMask.end(), 0);

    long flipCount = 0;          // Tracks the number of row flips
    int initialParity = -1;      // Stores the parity pattern of the first row

    // Iterate over each row of the board
    for (long x = 0, y = boardSize - 1; x < boardSize; ++x) {
        int blackDiskCount = 0;  // Counts black disks in the current row

        // Determine the range of y-coordinates that satisfy (N-1)^2 <= x^2 + y^2 < N^2
        for (y++; y >= 0; y--) {
            long distanceSquared = y * y + x * x;

            if (distanceSquared >= boardSize * boardSize) {
                continue; // Disk is outside the outer circle; remains white
            }

            if ((boardSize - 1) * (boardSize - 1) <= distanceSquared) {
                ++blackDiskCount; // Disk is within the annulus; it's black
            } else {
                break; // No need to check smaller y since distance decreases
            }
        }

        // If the number of black disks in the row is odd, mark this row for flipping
        if (blackDiskCount % 2 == 1) {
            flipCount++;
            setBit(rowFlipMask, x);
        }

        // Establish a parity pattern based on the first row
        if (initialParity == -1) {
            initialParity = blackDiskCount % 2;
        } else if (initialParity != (blackDiskCount % 2) && boardSize % 2 == 1) {
            // If parity is inconsistent and board size is odd, the configuration is unsolvable            
            return 0;
        }
    }

    // Calculate an initial estimate of total flips based on row flips
    flipCount = flipCount * (boardSize - flipCount) * 2;

    // Adjust the flip count by considering column interactions
    for (long x = 0, y = boardSize - 1; x < boardSize; ++x) {
        for (y++; y >= 0; y--) {
            long distanceSquared = y * y + x * x;

            if (distanceSquared >= boardSize * boardSize) {
                continue; // Disk is outside the outer circle; remains white
            }

            if ((boardSize - 1) * (boardSize - 1) <= distanceSquared) {
                // Determine the current state after row and column flips
                bool currentState = getBit(rowFlipMask, x) ^ getBit(rowFlipMask, y);

                if (currentState) {
                    flipCount -= 1; // Adjust flip count based on inconsistency
                } else {
                    flipCount += 1; // Adjust flip count based on consistency
                }
            } else {
                break; // No need to check smaller y since distance decreases
            }
        }
    }

    return flipCount;
}

int main() {
    // Initialize the bitmask with enough space to handle the largest board size
    // Each uint32_t can store 32 bits (rows)
    // Number of uint32_t needed = ceil(boardSize / 32)
    // For N = 2^31 - 31, this would be (2^31 - 31) / 32 + 1
    rowFlipMask.resize((1L << MAX_EXPONENT) / 32 + 1, 0);

    long totalFlips = 3; // Start with T(5) = 3 as given in the problem statement

    // Iterate over exponents from 4 to MAX_EXPONENT (31), stepping by 2
    for (int exponent = 4; exponent <= MAX_EXPONENT; exponent += 2) {
        long boardSize = (1L << exponent) - exponent; // N = 2^i - i
        
        //std::cout << "Checking board size N = " << boardSize 
        //          << " (2^" << exponent << " - " << exponent << ")" << std::endl;

        long minimalFlips = computeMinimalFlips(boardSize);
        totalFlips += minimalFlips;
    }

    // Output the final sum of T(N) for the specified range
    std::cout << totalFlips << std::endl;
    return 0;
}
