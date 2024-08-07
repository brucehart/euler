#include <iostream>
#include <vector>

// Function to calculate the number of distinct ways a player can checkout with a score less than the limit.
int solution(int limit) {
    // Create vectors for singles, doubles, and triples
    std::vector<int> singles;
    for (int i = 1; i <= 20; ++i) {
        singles.push_back(i);
    }
    //add bullseye
    singles.push_back(25);

    std::vector<int> doubles;
    for (int i = 1; i <= 20; ++i) {
        doubles.push_back(2 * i);
    }
    //add double bullseye
    doubles.push_back(50);

    std::vector<int> triples;
    for (int i = 1; i <= 20; ++i) {
        triples.push_back(3 * i);
    }

    // Combine all values and add a zero for scenarios with less than 3 throws
    std::vector<int> all_values = singles;
    all_values.insert(all_values.end(), doubles.begin(), doubles.end());
    all_values.insert(all_values.end(), triples.begin(), triples.end());
    all_values.push_back(0);

    int num_checkouts = 0;

    // Iterate through all possible combinations of double and two other throws
    for (int double_value : doubles) {
        for (size_t i = 0; i < all_values.size(); ++i) {
            for (size_t j = i; j < all_values.size(); ++j) {
                int throw1 = all_values[i];
                int throw2 = all_values[j];
                int checkout_total = double_value + throw1 + throw2;
                // Check if the checkout total is less than the limit
                if (checkout_total < limit) {
                    num_checkouts++;
                }
            }
        }
    }

    return num_checkouts;
}

int main() {
    int limit = 100;  // Default limit
    int num_checkouts = solution(limit);  // Calculate the number of distinct checkouts
    std::cout << num_checkouts << std::endl;  // Print the result
    return 0;
}
