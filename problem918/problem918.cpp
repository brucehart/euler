#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
typedef long long ll;

// Memoization map
std::unordered_map<ll, ll> memo;

// Recursive function to compute S(N)
// Recurrence relation: S(2N) = S(N-1) - S(N) + 4 , S(2N+1) = 3*S(N) + 4 - 3*S(N+1)
ll compute_S(ll N) {
    if (N == 0) return 0;
    if (N == 1) return 1;
    if (memo.find(N) != memo.end()) return memo[N];
    
    ll res;
    if (N % 2 == 0) {
        ll k = N / 2;
        res = compute_S(k - 1) - compute_S(k) + 4;
    }
    else {
        ll k = (N - 1) / 2;
        res = 3 * compute_S(k) + 4 - 3 * compute_S(k + 1);
    }
    memo[N] = res;
    return res;
}

int main(){
    ll N = 1000000000000LL; // 10^12
    ll result = compute_S(N);
    std::cout << result << std::endl;
}
