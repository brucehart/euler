#include <iostream>

int main() {
    const int maxCoord = 50;
    int count = 0;

    // Iterate over all possible points P(x1, y1) and Q(x2, y2)
    for (int x1 = 0; x1 <= maxCoord; ++x1) {
        for (int y1 = 0; y1 <= maxCoord; ++y1) {
            for (int x2 = 0; x2 <= maxCoord; ++x2) {
                for (int y2 = 0; y2 <= maxCoord; ++y2) {
                    // Avoid counting the same pair (P, Q) as (Q, P) by ensuring P is "less" than Q
                    if ((x1 < x2) || (x1 == x2 && y1 < y2)) {
                        // Case 1: Right angle at the origin (O)
                        if ((x1 != 0 || y1 != 0) && (x2 != 0 || y2 != 0)) {
                            if (x1 * x2 + y1 * y2 == 0) {
                                ++count;
                            }
                        }
                        // Case 2: Right angle at point P (x1, y1)
                        if ((x1 != 0 || y1 != 0) && (x2 != 0 || y2 != 0) && !(x1 == x2 && y1 == y2)) {
                            if (x1 * (x1 - x2) + y1 * (y1 - y2) == 0) {
                                ++count;
                            }
                        }
                        // Case 3: Right angle at point Q (x2, y2)
                        if ((x1 != 0 || y1 != 0) && (x2 != 0 || y2 != 0) && !(x1 == x2 && y1 == y2)) {
                            if (x2 * (x2 - x1) + y2 * (y2 - y1) == 0) {
                                ++count;
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << count << std::endl;

    return 0;
}
