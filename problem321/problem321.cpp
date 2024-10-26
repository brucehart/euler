#include <iostream>
#include <set>

// Typedef for convenience
typedef unsigned long long ull;

int main() {
    // M(n) = x * (x + 2) and triangle numbers are y * (y + 1) / 2
    // Forms a Pell equation k^2 - 8 * m^2 = -7 where n = (m - 1)
    // Two minimum solutions are (1, 1) and (2, 5) and the recurrence relation is
    // (k_n+1, m_n+1) = (3 * k_n + 8 * m_n, k_n + 3 * m_n)

    std::set<ull> unique_n_values;

    // Initial values for the first two solutions
    ull m1 = 1, k1 = 1;
    ull m2 = 2, k2 = 5;

    // Skip the zero case (m1 - 1)
    unique_n_values.insert(m2 - 1);

    // Calculate 40 terms using recurrence relations
    for (int i = 0; i < 40; ++i) {
        ull m1_next = k1 + 3 * m1;
        ull k1_next = 3 * k1 + 8 * m1;

        ull m2_next = k2 + 3 * m2;
        ull k2_next = 3 * k2 + 8 * m2;

        // Update values
        m1 = m1_next;
        k1 = k1_next;

        m2 = m2_next;
        k2 = k2_next;

        // Store (m - 1) values in the set
        unique_n_values.insert(m1 - 1);
        unique_n_values.insert(m2 - 1);
    }

    // Calculate the sum of the first 40 unique values
    ull sum = 0;
    int count = 0;
    for (const auto& value : unique_n_values) {
        if (count >= 40) break;        
        sum += value;
        ++count;
    }

    // Output the result
    std::cout << sum << std::endl;

    return 0;
}
