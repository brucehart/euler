#include <bits/stdc++.h>

typedef long long ll;

int main(){    
    const int u = 100000000;
    const int k = 100000;
    const int N = u; // Corrected upper bound: 100,000,000
    
    // Step 1: Compute the number of divisors using sieve-like method
    // Initialize divisor counts
    // Using unsigned short as d(n) <= 1000 for n <= 1e8
    std::vector<unsigned short> divisors(N + 1, 1); // d(1) =1

    // Sieve of Eratosthenes to identify prime numbers up to N
    std::vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for(int p = 2; p * p <= N; ++p){
        if(is_prime[p]){
            for(int multiple = p * p; multiple <= N; multiple += p){
                is_prime[multiple] = false;
            }
        }
    }

    // Iterate through all primes and update divisor counts
    for(int p = 2; p <= N; ++p){
        if(is_prime[p]){
            // For each multiple of prime p
            for(int multiple = p; multiple <= N; multiple += p){
                int count = 0;
                int m = multiple;
                // Count exponent of p in multiple
                while(m % p == 0){
                    count++;
                    m /= p;
                }
                // Update divisor count by multiplying with (exponent + 1)
                divisors[multiple] *= (count + 1);
            }
        }
    }

    // Step 2: Sliding window maximum using deque
    std::deque<int> dq;
    ll S = 0;

    for(int j = 1; j <= N; ++j){
        // Remove elements from the back that have a smaller or equal divisor count
        while(!dq.empty() && divisors[j] >= divisors[dq.back()]){
            dq.pop_back();
        }
        // Add current index to the deque
        dq.push_back(j);

        // Remove elements from the front that are outside the current window
        while(!dq.empty() && dq.front() < j - k + 1){
            dq.pop_front();
        }

        // Once the first k elements are processed, start accumulating the maximum
        if(j >= k){
            S += divisors[dq.front()];
        }
    }

    // Output the final sum S
    std::cout << S << std::endl;
}
