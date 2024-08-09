#include <iostream>
#include <vector>
#include <string>
#include <random>

typedef std::vector<unsigned char> DigitSequence;

// Store all the guesses made by the player
std::vector<DigitSequence> allGuesses;

// Store the number of matching digits for each guess
std::vector<unsigned int> matchingDigits;

// Function to generate a random number between 0 and 9
unsigned int generateRandomNumber(unsigned int modulo) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, modulo - 1);
    return dist(gen);
}

// Replace the digit with a new random digit (0-9)
void replaceWithRandomDigit(unsigned char &digit) {
    unsigned char previousDigit = digit;
    do {
        digit = generateRandomNumber(10);
    } while (digit == previousDigit);
}

// Store a player's guess and the number of correct matches
void storeGuess(const std::string &playerGuess, unsigned int correctMatches) {
    DigitSequence guessSequence;
    for (char c : playerGuess) {
        guessSequence.push_back(c - '0');
    }
    allGuesses.push_back(guessSequence);
    matchingDigits.push_back(correctMatches);
}

// Compute the difference between the guessed sequence and the actual sequence
unsigned int calculateMismatch(const DigitSequence &currentSequence) {
    unsigned int totalErrors = 0;

    for (unsigned int i = 0; i < allGuesses.size(); i++) {
        unsigned int matchingCount = 0;
        for (unsigned int j = 0; j < currentSequence.size(); j++) {
            if (currentSequence[j] == allGuesses[i][j]) {
                matchingCount++;
            }
        }

        if (matchingCount > matchingDigits[i]) {
            totalErrors += matchingCount - matchingDigits[i];
        } else {
            totalErrors += matchingDigits[i] - matchingCount;
        }
    }

    return totalErrors;
}

int main() {
    // Setting up 22 guesses and their corresponding correct matches
    std::string guesses[22] = {
        "5616185650518293", "3847439647293047", "5855462940810587",
        "9742855507068353", "4296849643607543", "3174248439465858",
        "4513559094146117", "7890971548908067", "8157356344118483",
        "2615250744386899", "8690095851526254", "6375711915077050",
        "6913859173121360", "6442889055042768", "2321386104303845",
        "2326509471271448", "5251583379644322", "1748270476758276",
        "4895722652190306", "3041631117224635", "1841236454324589",
        "2659862637316867"
    };

    unsigned int matches[22] = {
        2, 1, 3, 3, 3, 1, 2, 3, 1, 2, 3, 1, 1, 2, 0, 2, 2, 3, 1, 3, 3, 2
    };

    for (int i = 0; i < 22; ++i) {
        storeGuess(guesses[i], matches[i]);
    }

    // Initialize a random sequence for guessing
    const unsigned int numberOfDigits = allGuesses.front().size();
    DigitSequence currentSequence(numberOfDigits, 0);
    for (auto &digit : currentSequence) {
        replaceWithRandomDigit(digit);
    }

    const unsigned int maxAttemptsWithoutImprovement = 21;  // Threshold for random mutation
    unsigned int unsuccessfulAttempts = 0;

    unsigned int currentErrors = calculateMismatch(currentSequence);
    unsigned int previousErrors = currentErrors;

    // Iterate until a perfect sequence is found
    while (currentErrors != 0) {
        for (auto &digit : currentSequence) {
            unsigned char previousDigit = digit;
            replaceWithRandomDigit(digit);

            unsigned int newErrors = calculateMismatch(currentSequence);
            if (newErrors <= currentErrors) {
                currentErrors = newErrors;
            } else {
                digit = previousDigit;
            }
        }

        if (currentErrors == previousErrors) {
            unsuccessfulAttempts++;
            if (unsuccessfulAttempts == maxAttemptsWithoutImprovement) {
                replaceWithRandomDigit(currentSequence[generateRandomNumber(currentSequence.size())]);
                currentErrors = calculateMismatch(currentSequence);
                unsuccessfulAttempts = 0;
            }
        } else {
            unsuccessfulAttempts = 0;
            previousErrors = currentErrors;
        }
    }

    // Output the correct sequence
    for (unsigned char c : currentSequence) {
        std::cout << int(c);
    }
    std::cout << std::endl;

    return 0;
}

