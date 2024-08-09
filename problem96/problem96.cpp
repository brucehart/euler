#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

// Function to check if placing num in the position (row, col) is valid
bool isValid(int* puzzle, int row, int col, int num) {
    for (int x = 0; x < 9; ++x) {
        if (puzzle[row * 9 + x] == num || puzzle[x * 9 + col] == num ||
            puzzle[(row / 3 * 3 + x / 3) * 9 + (col / 3 * 3 + x % 3)] == num) {
            return false;
        }
    }
    return true;
}

// Recursive function to solve the Sudoku puzzle using backtracking
bool solve(int* puzzle) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (puzzle[row * 9 + col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(puzzle, row, col, num)) {
                        puzzle[row * 9 + col] = num;
                        if (solve(puzzle)) {
                            return true;
                        }
                        puzzle[row * 9 + col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle
bool solvePuzzle(int* puzzle) {
    return solve(puzzle);
}

int getPuzzleSum(int* puzzle) {
    return puzzle[0]*100 + puzzle[1]*10 + puzzle[2];
}

void readAndSolvePuzzles(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    int puzzle[81];
    int index = 0;
    int totalSum = 0;

    while (std::getline(file, line)) {
        if (line.find("Grid") != std::string::npos) {
            if (index > 0) {
                if (solvePuzzle(puzzle)) {
                    totalSum += getPuzzleSum(puzzle);
                }
            }
            index = 0;
        } else {
            for (char ch : line) {
                puzzle[index++] = ch - '0';
            }
        }
    }

    // Solve the last puzzle
    if (index == 81) {
        if (solvePuzzle(puzzle)) {
            totalSum += getPuzzleSum(puzzle);
        }
    }

    file.close();

    std::cout << totalSum << std::endl;
}

int main() {
    std::string filename = "p096_sudoku.txt";
    readAndSolvePuzzles(filename);
    return 0;
}
