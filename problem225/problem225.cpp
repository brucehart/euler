#include <iostream>
#include <array>

// This constant defines the position in the sequence we are interested in
const int TARGET_INDEX = 124;

// Function that advances the Tribonacci sequence by one step
void advanceTribonacci(std::array<int, 3>& state, int modulus) {
    int firstElement = state[0];
    int secondElement = state[1];
    int thirdElement = state[2];
    
    // Shift the elements and compute the next value in the sequence modulo 'modulus'
    state[0] = secondElement;
    state[1] = thirdElement;
    state[2] = (firstElement + secondElement + thirdElement) % modulus;
}

// Function that checks if any term in the Tribonacci sequence is a multiple of the given modulus
bool hasTribonacciMultiple(int modulus) {
    std::array<int, 3> slowState = {1, 1, 1};  // Slow pointer in Floyd's cycle-finding algorithm
    std::array<int, 3> fastState = slowState;  // Fast pointer in Floyd's cycle-finding algorithm

    bool isHead = true;  // Flag to indicate the first iteration
    while (true) {
        if (slowState[0] % modulus == 0)  // Check if the first element is divisible by modulus
            return true;
        if (!isHead && slowState == fastState)  // If the slow and fast pointers are equal, a cycle is detected
            return false;

        // Advance both the slow and fast pointers through the Tribonacci sequence
        advanceTribonacci(slowState, modulus);
        advanceTribonacci(fastState, modulus);
        advanceTribonacci(fastState, modulus);

        isHead = false;  // After the first iteration, isHead becomes false
    }
}

// Function that finds the odd number at the TARGET_INDEX position
std::string findOddNumberAtTargetIndex() {
    int currentCount = 0;  // Counter for valid numbers found
    for (int currentNumber = 1;; currentNumber += 2) {  // Loop through odd numbers
        if (!hasTribonacciMultiple(currentNumber)) {  // Check if the current number has a Tribonacci multiple
            currentCount++;
            if (currentCount == TARGET_INDEX)  // If we've reached the target index
                return std::to_string(currentNumber);
        }
    }
}

int main() {
    // Find and print the odd number at the TARGET_INDEX position that does not have any Tribonacci multiple
    std::cout << findOddNumberAtTargetIndex() << std::endl;
    return 0;
}
