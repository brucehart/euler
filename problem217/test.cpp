#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

// Structure to hold count and sum for DP states
struct DPCell {
    cpp_int count;
    cpp_int sum;
};

// Function to compute the sum of all k-digit numbers with digit sum n
cpp_int compute_sum_of_numbers(int k, int n) {
    // Edge case checks
    if (k <= 0) {
        // No digits, no numbers
        return 0;
    }
    if (n < 1 || n > 9 * k) {
        // Sum is too small or too large to be achieved with k digits
        return 0;
    }

    // Initialize DP table with (k+1) rows and (n+1) columns
    // DP[i][s] = pair<count, sum> for i-digit numbers with digit sum s
    vector<vector<DPCell>> DP(k + 1, vector<DPCell>(n + 1, DPCell{0, 0}));

    // Base case: 0-digit number with sum 0
    DP[0][0].count = 1;
    DP[0][0].sum = 0;

    // Fill the DP table
    for (int i = 1; i <= k; ++i) {
        // Determine the range of digits based on the position
        int start_d = (i == 1) ? 1 : 0; // First digit cannot be 0
        int end_d = 9;

        for (int s = 0; s <= n; ++s) {
            for (int d = start_d; d <= end_d; ++d) {
                if (s - d >= 0) {
                    DP[i][s].count += DP[i - 1][s - d].count;
                    DP[i][s].sum += DP[i - 1][s - d].sum * 10 + d * DP[i - 1][s - d].count;
                }
            }
        }
    }

    return DP[k][n].sum;
}

// Function to compute the count of all k-digit numbers with digit sum n
cpp_int compute_count_of_numbers(int k, int n) {
    // Edge case checks
    if (k <= 0) {
        // No digits, no numbers
        return 0;
    }
    if (n < 1 || n > 9 * k) {
        // Sum is too small or too large to be achieved with k digits
        return 0;
    }

    // Initialize DP table with (k+1) rows and (n+1) columns
    // DP[i][s] = pair<count, sum> for i-digit numbers with digit sum s
    vector<vector<DPCell>> DP(k + 1, vector<DPCell>(n + 1, DPCell{0, 0}));

    // Base case: 0-digit number with sum 0
    DP[0][0].count = 1;
    DP[0][0].sum = 0;

    // Fill the DP table
    for (int i = 1; i <= k; ++i) {
        // Determine the range of digits based on the position
        int start_d = (i == 1) ? 1 : 0; // First digit cannot be 0
        int end_d = 9;

        for (int s = 0; s <= n; ++s) {
            for (int d = start_d; d <= end_d; ++d) {
                if (s - d >= 0) {
                    DP[i][s].count += DP[i - 1][s - d].count;
                    DP[i][s].sum += DP[i - 1][s - d].sum * 10 + d * DP[i - 1][s - d].count;
                }
            }
        }
    }

    return DP[k][n].count;
}

int main() {
    int k, n;

    cout << "Enter the number of digits (k): ";
    cin >> k;

    cout << "Enter the desired digit sum (n): ";
    cin >> n;

    // Compute the count of valid numbers
    cpp_int count = compute_count_of_numbers(k, n);

    // Compute the sum of valid numbers
    cpp_int total_sum = compute_sum_of_numbers(k, n);

    cout << "\nNumber of unique " << k << "-digit numbers with digit sum " << n << " is:\n" << count << endl;
    cout << "Sum of all " << k << "-digit numbers with digit sum " << n << " is:\n" << total_sum << endl;

    return 0;
}
