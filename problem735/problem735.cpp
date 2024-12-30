#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <string>

// -----------------------------------------------------------------------------
// 1) Prime sieve up to 1e6 (since sqrt(1e12) = 1e6).
//    We'll store these primes in a global vector for factorization use.
// -----------------------------------------------------------------------------
static const int MAXP = 1000000;  // 1e6
static std::vector<int> primes;   // All primes up to 1e6

void build_prime_sieve()
{
    std::vector<bool> isprime(MAXP+1, true);
    isprime[0] = false;
    isprime[1] = false;
    for(int p = 2; p*p <= MAXP; ++p) {
        if(isprime[p]) {
            for(int q = p*p; q <= MAXP; q += p) {
                isprime[q] = false;
            }
        }
    }
    for(int p = 2; p <= MAXP; ++p) {
        if(isprime[p]) {
            primes.push_back(p);
        }
    }
}

// -----------------------------------------------------------------------------
// 2) Factor an integer n (<= 1e12) into its prime factorization using the primes
//    from the sieve. Return a vector of (prime, exponent).
//    We'll do trial division up to sqrt(n). 
// -----------------------------------------------------------------------------
static std::vector<std::pair<int64_t, int>> factorize_int64(int64_t n)
{
    std::vector<std::pair<int64_t,int>> res;
    for (int p : primes) {
        if ((int64_t)p * p > n) break;
        if (n % p == 0) {
            int c = 0;
            while (n % p == 0) {
                n /= p;
                c++;
            }
            res.push_back({p,c});
        }
    }
    // If remainder > 1, it's prime
    if (n > 1) {
        res.push_back({n, 1});
    }
    return res;
}

// -----------------------------------------------------------------------------
// 3) Count the number of divisors d of n^2 that are <= X (where n^2 = product of
//    prime^(2*exponent)). We'll do a backtracking approach. 
// -----------------------------------------------------------------------------

static const int MEMO_SIZE = 200000;  // somewhat large but not huge

struct DivCountVal {
    int64_t n;
    int64_t X;
    int64_t count; // result
    // LRU or usage stats could go here, omitted for brevity
};

static std::vector<DivCountVal> g_divcount_cache; // trivial "cache"

// Simple helper to see if (n, X) is in cache
bool cache_get(int64_t n, int64_t X, int64_t &outVal)
{
    for (auto &ent : g_divcount_cache) {
        if (ent.n == n && ent.X == X) {
            outVal = ent.count;
            return true;
        }
    }
    return false;
}

// Insert into cache (super naive). If full, evict front.
void cache_put(int64_t n, int64_t X, int64_t val)
{
    if ((int)g_divcount_cache.size() >= MEMO_SIZE) {
        static int evictIndex = 0;
        g_divcount_cache[evictIndex] = {n, X, val};
        evictIndex = (evictIndex + 1) % MEMO_SIZE;
    } else {
        g_divcount_cache.push_back({n, X, val});
    }
}

// Recursive function to enumerate divisors of n^2 up to X
static int64_t backtrack_divcount_leqX(
    const std::vector<std::pair<int64_t,int>> &primeFactors,
    int idx,
    int64_t currentDiv,
    int64_t X)
{
    // If we've placed exponents for all prime factors, we have a valid divisor:
    if (idx == (int)primeFactors.size()) {
        return (currentDiv <= X) ? 1 : 0;
    }

    int64_t p = primeFactors[idx].first;
    int e     = primeFactors[idx].second;
    // In n^2, exponent is 2*e. So we can choose exponent k in [0..2*e].
    int maxExp = 2*e;

    int64_t count = 0;
    int64_t val = 1;
    for (int k = 0; k <= maxExp; k++) {
        int64_t nextDiv = currentDiv * val;
        if (nextDiv > X) {
            break; 
        }
        count += backtrack_divcount_leqX(primeFactors, idx+1, nextDiv, X);
        if (k < maxExp) {
            if (val > X / p) {
                break;
            }
            val *= p;
        }
    }
    return count;
}

static int64_t countDivisorsOfN2UpToX(int64_t n, int64_t X)
{
    if (X <= 0) return 0;
    if (n == 0) return 0;

    // check cache
    int64_t cached;
    if (cache_get(n, X, cached)) {
        return cached;
    }

    // factor n
    std::vector<std::pair<int64_t,int>> pf = factorize_int64(n);
    // backtrack to count
    int64_t ans = backtrack_divcount_leqX(pf, 0, 1LL, X);

    // store in cache
    cache_put(n, X, ans);
    return ans;
}

// -----------------------------------------------------------------------------
// 4) Count the number of *odd* divisors of n^2 up to X.
// -----------------------------------------------------------------------------
static int64_t countOddDivisorsOfN2UpToX(int64_t n, int64_t X)
{
    if (X <= 0) return 0;

    // Factor out power of 2 from n
    int64_t tmp = n;
    int twoExp = 0;
    while ((tmp % 2) == 0) {
        tmp /= 2;
        twoExp++;
    }

    // If tmp=1 => n was a power of 2 => exactly 1 odd divisor = 1 (if <= X).
    if (tmp == 1) {
        return (X >= 1) ? 1 : 0;
    }

    // Factorize tmp (odd part)
    auto pf = factorize_int64(tmp);

    // Backtrack to count divisors of tmp^2 <= X
    std::function<int64_t(int,int64_t)> dfs = [&](int idx, int64_t curVal) -> int64_t {
        if (idx == (int)pf.size()) {
            return (curVal <= X) ? 1 : 0;
        }
        int64_t p = pf[idx].first;
        int e     = pf[idx].second;
        int maxE  = 2*e; 
        int64_t c = 0;
        int64_t mul = 1;
        for(int k=0; k <= maxE; ++k) {
            int64_t nxt = curVal * mul;
            if (nxt > X) break;
            c += dfs(idx+1, nxt);
            if (k < maxE) {
                if (mul > X / p) break;
                mul *= p;
            }
        }
        return c;
    };

    int64_t ans = dfs(0, 1LL);
    return ans;
}

// -----------------------------------------------------------------------------
// 5) Putting it all together: 
//    f(n) = # of odd divisors of n^2 <= n  +  # of divisors of n^2 <= floor(n/2)
//    We want sum_{n=1..N} f(n).
// -----------------------------------------------------------------------------

static __int128 sumF_up_to(int64_t N)
{
    __int128 total = 0;
    int64_t limit = (int64_t)std::floor(std::sqrt((long double)N));

    // --- Phase 1: direct sum for n in [1..limit]
    for (int64_t n = 1; n <= limit; ++n) {
        std::cout << n << std::endl;
        int64_t oddC = countOddDivisorsOfN2UpToX(n, n);
        int64_t allC = countDivisorsOfN2UpToX(n, n/2);
        total += (oddC + allC);
    }

    // --- Phase 2: handle n in (limit..N] via interval grouping
    int64_t start = limit + 1; 
    while (start <= N) {
        int64_t val = N / start;
        if (val == 0) {
            break;
        }
        int64_t end = N / val;
        if (end > N) end = N;

        // Direct loop (in practice you'd optimize with a typical "divisor sum" approach)
        for (int64_t n = start; n <= end; ++n) {
            int64_t oddC = countOddDivisorsOfN2UpToX(n, n);
            int64_t allC = countDivisorsOfN2UpToX(n, n/2);
            total += (oddC + allC);
        }
        start = end + 1;
    }

    return total;
}

// -----------------------------------------------------------------------------
// 6) The main solve() function
// -----------------------------------------------------------------------------

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Build prime sieve
    build_prime_sieve();

    // Read input N
    long long N = 1000000000000LL;
    

    // We compute F(N) using the function above:
    __int128 ans128 = sumF_up_to(N);

    // Convert __int128 to string:
    auto toString128 = [&](__int128 x){
        if (x == 0) return std::string("0");
        bool neg = (x < 0);
        if (neg) x = -x;
        std::string s;
        while (x > 0) {
            int digit = (int)(x % 10);
            s.push_back(char('0' + digit));
            x /= 10;
        }
        if (neg) s.push_back('-');
        std::reverse(s.begin(), s.end());
        return s;
    };

    // Print result
    std::cout << toString128(ans128) << "\n";
    return 0;
}
