#include <iostream>
#include <vector>
#include <cmath>

int calculateMaxPrizeFund(int turns) {
    // Initialize a 2D vector to store probabilities for each turn and each possible number of blue discs
    std::vector<std::vector<double>> p(turns + 1);

    // Populate the probability matrix with zeros for each possible outcome
    for (int turn = 2; turn <= turns + 1; ++turn) {
        p[turn - 2] = std::vector<double>(turn, 0.0);
    }

    // Set the initial probabilities for the first turn (50% chance for blue or red disc)
    p[0][0] = 0.5; // Probability of getting one blue disc
    p[0][1] = 0.5; // Probability of getting one red disc

    // Calculate probabilities for each subsequent turn
    for (int currentTurn = 1; currentTurn < p.size(); ++currentTurn) {
        for (int blueCount = 0; blueCount < p[currentTurn].size(); ++blueCount) {
            if (blueCount == 0) {
                // If no blue discs so far, the probability comes from having all reds previously
                p[currentTurn][blueCount] += (1.0 / (currentTurn + 2)) * p[currentTurn - 1][blueCount];
            } else if (blueCount == p[currentTurn].size() - 1) {
                // If all discs are blue so far, the probability comes from having all blues previously
                p[currentTurn][blueCount] += ((currentTurn + 1.0) / (currentTurn + 2)) * p[currentTurn - 1][blueCount - 1];
            } else {
                // Otherwise, consider both possibilities: adding a blue or red disc
                p[currentTurn][blueCount] += ((currentTurn + 1.0) / (currentTurn + 2)) * p[currentTurn - 1][blueCount - 1]
                                           + (1.0 / (currentTurn + 2)) * p[currentTurn - 1][blueCount];
            }
        }
    }

    // Sum the probabilities where the number of blue discs exceeds the number of red discs
    double winningProbSum = 0.0;
    for (int blueCount = 0; blueCount < (turns + 1) / 2; ++blueCount) {
        winningProbSum += p[turns - 1][blueCount];
    }

    // Calculate the maximum prize fund by taking the reciprocal of the winning probability sum and flooring the result
    return std::floor(1.0 / winningProbSum);
}

int main() {
    int numberOfTurns = 15; // Number of turns to consider in the game
    int maxPrizeFund = calculateMaxPrizeFund(numberOfTurns); // Calculate the maximum prize fund for the given number of turns
    std::cout << maxPrizeFund << std::endl; // Output the result
    return 0;
}
