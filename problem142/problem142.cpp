#include <iostream>
#include <cmath>

// Function to check if a number is a perfect square
bool isSquare(int x) {
    int root = static_cast<int>(sqrt(x)); // Compute the integer square root of x
    return root * root == x;             // Check if the square of the root equals x
}

int main() {
    bool solved = false; // Flag to indicate if a solution has been found
    int i = 4;           // Starting value for i

    // Continue looping until a solution is found
    while (!solved) {
        int a = i * i; // Compute the value of a

        // Iterate through possible values of j
        for (int j = 3; j < i; ++j) {
            if (solved) break; // Break the loop if a solution is found

            int c = j * j;      // Compute the value of c
            int f = a - c;      // Calculate f

            if (!isSquare(f)) continue; // Skip if f is not a perfect square

            int k_initial = 1; // Start value for k

            // Adjust k_initial if j is even
            if (j % 2 == 0) {
                k_initial = 2;
            }

            // Iterate through possible values of k
            for (int k = k_initial; k < j; k += 2) {
                int d = k * k;     // Compute the value of d
                int e = a - d;    // Calculate e
                int b = c - e;    // Calculate b

                // Skip invalid cases
                if (b <= 0 || !isSquare(e) || !isSquare(b)) continue;

                // Calculate x, y, z based on the equations
                int x = (a + b) / 2;
                int y = (e + f) / 2;
                int z = (c - d) / 2;
                int result = x + y + z;

                // Print the result
                std::cout << result << std::endl;

                solved = true; // Mark the solution as found
                break;
            }
        }

        i++; // Increment i for the next iteration
    }

    return 0; // End of program
}

