#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <string>

/// Function to generate a canonical representation of the hexagon
/// to avoid counting congruent hexagons multiple times
std::string canonical_form(int s1, int s2, int s3, int s4, int s5, int s6) {
    std::vector<int> sides = {s1, s2, s3, s4, s5, s6};
    std::vector<std::vector<int>> all_rotations;

    // Generate all cyclic rotations
    for (int i = 0; i < 6; ++i) {
        std::vector<int> rotation;
        for (int j = 0; j < 6; ++j) {
            rotation.push_back(sides[(i + j) % 6]);
        }
        all_rotations.push_back(rotation);
    }

    // Generate all reversed cyclic rotations (reflections)
    std::reverse(sides.begin(), sides.end());
    for (int i = 0; i < 6; ++i) {
        std::vector<int> rotation;
        for (int j = 0; j < 6; ++j) {
            rotation.push_back(sides[(i + j) % 6]);
        }
        all_rotations.push_back(rotation);
    }

    // Find the minimal rotation (lexicographically)
    std::vector<int> min_rotation = all_rotations[0];
    for (const auto& rotation : all_rotations) {
        if (rotation < min_rotation) {
            min_rotation = rotation;
        }
    }

    // Convert to string for hashing
    std::string key;
    for (int val : min_rotation) {
        key += std::to_string(val) + ",";
    }
    return key;
}

int main() {
    const int n = 55106;
    long long count = 0;

    std::unordered_set<std::string> hexagons; // To store unique hexagons

    // Upper bounds for variables based on perimeter constraint
    int s1_max = n / 2;
    std::cout << "s1_max: " << s1_max << std::endl;

    for (int s1 = 1; s1 <= s1_max; ++s1) {
        std::cout << "s1: " << s1 << std::endl;
        int s2_max = (n - 2 * s1) / 1;
        for (int s2 = 1; s2 <= s2_max; ++s2) {
            int s5_min = std::max(1, s1 + s2 - n / 2);
            int s5_max = std::min(s1 + s2 - 1, (n - 2 * s1 - s2) / 2);

            for (int s5 = s5_min; s5 <= s5_max; ++s5) {
                int s4 = s1 + s2 - s5;
                if (s4 <= 0) continue;

                int s6_max = (n - 2 * s1 - s2 - s5) / 2;
                for (int s6 = 1; s6 <= s6_max; ++s6) {
                    int s3 = s5 + s6 - s2;
                    if (s3 <= 0) continue;

                    int P = s1 + s2 + s3 + s4 + s5 + s6;
                    if (P > n) break;

                    // Generate canonical form to avoid duplicates
                    // std::string key = canonical_form(s1, s2, s3, s4, s5, s6);

                    // // Insert into set if not already present
                    // if (hexagons.find(key) == hexagons.end()) {
                    //     hexagons.insert(key);
                    //     ++count;
                    // }

                    count++;
                    //if (count % 1000 == 0) std::cout << count << std::endl;
                }
            }
        }
    }

    std::cout << "H(" << n << ") = " << count << std::endl;
    return 0;
}

