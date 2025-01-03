#include <iostream>
#include <vector>
#include <set>
#include <algorithm>         // for std::max
#include <boost/multiprecision/cpp_int.hpp>

// We use Boost's multiprecision library for safety when computing
// large cubic polynomials, before reducing modulo 1,000,000.
namespace mp = boost::multiprecision;

//
// A Disjoint Set Union (Union-Find) structure to efficiently track
// connected components among 1,000,000 possible phone numbers.
//
class DisjointSetUnion {
private:
    std::vector<int> parent;
    std::vector<int> size_; // "size_" to avoid collision with std::size()

public:
    DisjointSetUnion(int n) : parent(n), size_(n, 1) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find the representative (root) of the set that x belongs to,
    // with path compression optimization.
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union the sets of x and y (by size).
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            if (size_[rx] < size_[ry]) {
                std::swap(rx, ry);
            }
            // Now rx is the larger set, merge ry into rx
            parent[ry] = rx;
            size_[rx] += size_[ry];
        }
    }

    // Return the size of the set containing x.
    int compSize(int x) {
        return size_[find(x)];
    }
};

//
// We need to generate the infinite sequence S_k as follows:
//
//   For 1 <= k <= 55:
//     S_k = [100003 - 200003*k + 300007*k^3] mod 1,000,000
//
//   For k >= 56:
//     S_k = [S_{k-24} + S_{k-55}] mod 1,000,000
//
// Caller(n) = S_{2n - 1}, Called(n) = S_{2n}.
//
// We will compute S_k on the fly and store in a dynamic array.
// If k has not yet been computed, extend the sequence until S_k is available.
//

static const int MOD = 1000000;

// Global container for the sequence; we will fill it as needed.
std::vector<int> S;  
// How many terms have we initialized so far?
int generatedUpTo = 0;  

// Ensure that the sequence is generated at least up to index k.
// Indices here are 1-based for S_k.
void generateUpTo(int k) {
    // If we have already generated at least k terms, no need to do anything.
    if (generatedUpTo >= k) {
        return;
    }

    // If this is our first time, pre-compute S_1..S_55 using the polynomial:
    // 100003 - 200003*k + 300007*k^3 (mod 1,000,000)
    if (generatedUpTo == 0) {
        S.resize(std::max(k, 55) + 1, 0); 
        for (int i = 1; i <= 55; ++i) {
            // Use big integers for safety, then reduce mod 1,000,000.
            mp::cpp_int term = 100003;
            term -= mp::cpp_int(200003) * i;
            term += mp::cpp_int(300007) * i * i * i;
            // Reduce modulo 1,000,000:
            mp::cpp_int modTerm = term % MOD;
            if (modTerm < 0) {
                modTerm += MOD;  // handle negative remainder
            }
            S[i] = static_cast<int>(modTerm.convert_to<long long>());
        }
        generatedUpTo = 55;
    } else {
        // We already have some portion of S_1..S_55 computed, or more.
        // Make sure our vector is big enough for index k.
        if ((int)S.size() <= k) {
            S.resize(k + 1, 0);
        }
    }

    // Now generate up to S_k for k >= 56 using the relation:
    // S_m = (S_{m-24} + S_{m-55}) mod 1,000,000
    for (int i = generatedUpTo + 1; i <= k; ++i) {
        if (i <= 55) {
            // Already taken care of in the first pass, but just in case.
            continue;
        }
        S[i] = (S[i - 24] + S[i - 55]) % MOD;
    }
    generatedUpTo = k;
}

// Convenient function to return S_k. We generate as needed.
int getS(int k) {
    generateUpTo(k);
    return S[k];
}

int main() {
    // We have 1,000,000 users, numbered 0..999,999.
    // The problem states phone numbers are modulo 1,000,000, so that is
    // consistent with 0-based indexing in our DSU. The only subtlety is
    // the PM's number "524287". We'll also treat that as a 0-based index.
    // (If the problem truly uses 1-based phone numbers, we'd shift. 
    //  But typically phone number '524287' is just a label from 0..999999.)
    //
    // We'll assume the phone numbers from the sequence S_k are in [0..999999].
    // Then we simply pass them to union-find as 0-based integers.
    //
    // The PM's phone number is:
    const int primeMinister = 524287;

    // We want to know when the connected component that contains the PM
    // reaches 99% of the users = 990,000 users.
    const int targetSize = 990000;

    // Build union-find for 1,000,000 users.
    DisjointSetUnion dsu(1000000);

    long long successfulCalls = 0;  // we'll count successful calls.

    // We'll read calls one by one: n = 1, 2, 3, ...
    // Caller(n) = S_{2n-1}, Called(n) = S_{2n}.
    // If Caller(n) != Called(n), it's a successful call. Then union them.
    // After each successful call, check if the PM's component size >= 990000.
    // If so, stop and print the number of successful calls.

    for (long long n = 1; ; ++n) {
        int c = getS(2 * n - 1); // Caller
        int d = getS(2 * n);     // Called

        // Misdial if c == d, do not count as successful
        if (c != d) {
            // Union the two phone numbers
            dsu.unite(c, d);
            ++successfulCalls;

            // Check if PM's component is large enough
            if (dsu.compSize(primeMinister) >= targetSize) {
                std::cout << successfulCalls << std::endl;
                break;
            }
        }
    }

    return 0;
}

