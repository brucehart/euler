#include <iostream>
#include <cmath>
#include <iomanip>

// Function to determine the best bet to achieve a target win rate
int get_best_bet(int flips, double target, double stepSize = 0.00001) {
    int bestBet = 1000; // Initialize the best bet with a high value
    double currentBet = 0.0; // Start with a bet of 0.0

    // Iterate over possible bet values from 0.0 to 1.0
    while (currentBet <= 1.0) {
        double winRate = 1 + 2.0 * currentBet; // Calculate the win rate for the current bet
        double lossRate = 1 - currentBet; // Calculate the loss rate for the current bet

        int headsNeeded = flips; // Initialize the number of heads needed to the total number of flips
        // Determine the minimum number of heads needed to achieve the target win rate
        while (headsNeeded > 0) {
            if (pow(winRate, headsNeeded) * pow(lossRate, flips - headsNeeded) < target) {
                headsNeeded++;
                break;
            }
            headsNeeded--;
        }

        currentBet += stepSize; // Increment the current bet by the step size

        // Update the best bet if the current number of heads needed is lower
        if (bestBet > headsNeeded) {
            bestBet = headsNeeded;
        }
    }

    return bestBet; // Return the best bet found
}
// Calculate the factorial of a number (used in binomial coefficient calculation)
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

// Calculate the binomial coefficient "n choose k"
double binomialCoefficient(int n, int k) {
    double result = 1.0;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// Calculate the probability of at least 'n' heads in 'numFlips' fair coin flips
double probabilityAtLeastNHeads(int numFlips, int n) {
    double probability = 0.0;

    // Iterate from 'n' to 'numFlips' (inclusive) and sum the probabilities
    for (int i = n; i <= numFlips; ++i) {
        probability += binomialCoefficient(numFlips, i) / pow(2, numFlips);
    }

    return probability;
}

int main() {
    double billion = std::pow(10,9);
    int n = 1000;

    std::cout << std::fixed << std::setprecision(12);    
    std::cout << probabilityAtLeastNHeads(n,get_best_bet(n, billion)) << std::endl;
    return 0;
}