#include <iostream>

int main() {
    const int limit = 1000000;  // Maximum number of tiles
    int count = 0;              // To count the number of valid laminae

    // Iterate over possible inner square side lengths
    for (int innerSide = 1;; ++innerSide) {
        int squareSize = innerSide;  // Initialize square size with the current inner square size
        int tiles = 0;               // Initialize tile count
        int prevCount = count;       // Store the count before this iteration to detect changes

        // Continue adding layers until the number of tiles exceeds the limit
        while (tiles <= limit) {
            squareSize += 2;  // Increase the square size by adding one layer around
            tiles = squareSize * squareSize - innerSide * innerSide;  // Calculate the number of tiles used

            // If the number of tiles exceeds the limit, break the loop
            if (tiles > limit) break;

            count++;  // If valid, increment the count of possible laminae
        }

        // If no new laminae were found in this iteration, break the outer loop
        if (count == prevCount) break;
    }

    // Output the total number of valid square laminae
    std::cout << count << std::endl;

    return 0;
}
