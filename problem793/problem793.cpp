#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

/*
  We have a pseudo-random sequence defined by:
    S[0] = 290797
    S[i+1] = (S[i] * S[i]) % 50515093

  We want M(n), the median of all pairwise products S[i]*S[j] for
  0 <= i < j < n.

  Specifically, we are asked to find M(1,000,003). The total number
  of pairs is C(n, 2) = n*(n-1)/2. For n = 1,000,003 this count is:

      total_pairs = 1,000,003 * 1,000,002 / 2 = 500,002,500,003  (an odd number)

  The median for an odd-sized list is the element in the exact middle of
  the sorted list. In 1-based indexing, that position is:

      median_index = (total_pairs + 1) / 2 = 250,001,250,002

  We cannot store all products explicitly (which would be on the order
  of 5e11 products). Instead, we use a common technique to find the k-th
  order statistic (here, the median) via binary search on the product values.

  Steps:
    1. Generate the first n = 1,000,003 values of S.
    2. Sort this array of S.
    3. Use binary search over the possible product range [0, 50515092^2].
       - For a given candidate "mid":
         * Count how many pairwise products are <= mid.
         * If that count is >= median_index, move the upper bound down.
         * Otherwise, move the lower bound up.
    4. Once binary search converges, the lower bound is the median.

  To count how many products <= mid efficiently, we use a two-pointer
  approach on the sorted array:
    - Let i go from 0 to n-1 (inclusive).
    - Keep a pointer j, starting from the end of the array (j = n-1).
    - While S[i] * S[j] > mid, decrement j.
    - Then, all indices k from i+1..j form valid products <= mid with S[i].
      So we add (j - i) to our count.
    - We must ensure j > i so that we only count pairs (i < j).

  Because each j only moves left overall, the total complexity of this
  counting step is O(n) rather than O(n log n). Repeating this in the
  binary search (which is ~ log(50515092^2)) still yields a solution
  that is performant enough for this problem size if implemented in C++.
*/

static const int N = 1'000'003;
static const int MOD = 50'515'093;
static const int64_t MAX_S = 50'515'092; // maximum possible S[i]
static const int64_t MAX_PRODUCT = MAX_S * MAX_S; // up to ~2.55e15, fits in 64-bit

// Count how many distinct pairs (i < j) satisfy S[i]*S[j] <= x
int64_t countPairsLessEqual(const std::vector<int>& S, int64_t x) {
    int64_t count = 0;
    int j = static_cast<int>(S.size()) - 1;

    for (int i = 0; i < static_cast<int>(S.size()); ++i) {
        // Move j down while product is too large
        while (j > i && static_cast<int64_t>(S[i]) * S[j] > x) {
            --j;
        }
        if (j <= i) {
            // Once j <= i, there are no more valid pairs for this i
            // or any larger i, because j can only go left
            break;
        }
        // j > i and S[i]*S[j] <= x
        count += (j - i);
    }
    return count;
}

int main() {
    // 1) Generate the sequence
    std::vector<int> S(N);
    S[0] = 290797;
    for (int i = 0; i < N - 1; ++i) {
        // Use 64-bit intermediate to avoid overflow in multiplication
        int64_t nextVal = static_cast<int64_t>(S[i]) * S[i];
        S[i + 1] = static_cast<int>(nextVal % MOD);
    }

    // 2) Sort the sequence
    std::sort(S.begin(), S.end());

    // 3) We want the middle of the sorted pairwise products.
    //    total_pairs is odd => single middle element.
    int64_t total_pairs = static_cast<int64_t>(N) * (N - 1) / 2;
    int64_t median_index = (total_pairs + 1) / 2; // 1-based

    // Binary search bounds for the product
    int64_t lo = 0;
    int64_t hi = MAX_PRODUCT;

    while (lo < hi) {
        int64_t mid = lo + (hi - lo) / 2;
        // Count how many pairs are <= mid
        int64_t c = countPairsLessEqual(S, mid);

        if (c >= median_index) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    // 4) 'lo' is the median
    std::cout << lo << std::endl;
    return 0;
}

