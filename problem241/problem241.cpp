#include <iostream>
#include <algorithm>
#include <stack>
#include <tuple>
#include <numeric>

typedef unsigned long long ull;

// Global Variables
const ull N = 1000000000000000000ULL; // 10^18
ull sum_ans = 0;

// Function to find the smallest prime factor of n
ull smallest_prime_factor(ull n){
    if(n < 2){
        return 0; // Undefined, handle as needed
    }
    if(n % 2 == 0){
        return 2;
    }
    for(ull i = 3; i * i <= n; i += 2){
        if(n % i == 0){
            return i;
        }
    }
    return n; // n is prime
}

// Function to compute base^exp safely, returns N + 1 on overflow
ull pow_safe(ull base, int exp){
    if(base == 0 && exp > 0){
        return 0;
    }
    ull result = 1;
    for(int i = 0; i < exp; ++i){
        if(result > N / base){
            return N + 1; // Indicate overflow
        }
        result *= base;
    }
    return result;
}

int main(){
    // Use a stack to implement iterative DFS
    std::stack<std::tuple<ull, ull, ull>> stk;

    // Initialize DFS with odd numerators as per the problem's condition
    for(int x = 3; x <=15; x +=2){
        std::cout << x << std::endl;
        stk.emplace(1, (ull)x, 2);
    }

    // Define a threshold for the denominator to prevent infinite growth
    const ull DENOMINATOR_THRESHOLD = 1e12;

    while(!stk.empty()){
        ull current_n, numerator, denominator;
        std::tie(current_n, numerator, denominator) = stk.top();
        stk.pop();

        // Debugging output (comment out in final version)
        // std::cout << "Processing n: " << current_n << ", numerator: " << numerator 
        //           << ", denominator: " << denominator << "\n";

        // Prune paths that exceed the limit or are not coprime
        if(current_n > N / numerator || std::gcd(current_n, denominator) != 1){
            continue;
        }

        // If p(n) has been adjusted to 1, add current_n to the sum
        if(numerator ==1 && denominator ==1){
            sum_ans += current_n;
        }

        // If denominator is 1 but numerator is not, no further action is needed
        if(denominator ==1){
            continue;
        }

        // Additional termination condition to prevent infinite growth
        if(denominator > DENOMINATOR_THRESHOLD){
            continue;
        }

        // Find the smallest prime factor of denominator
        ull p = smallest_prime_factor(denominator);
        if(p ==0){
            continue; // Undefined, skip
        }
        int e = 1;

        // Determine the maximum exponent e such that p^(e+1) divides denominator
        while(true){
            ull p_power = pow_safe(p, e + 1);
            if(p_power >= N + 1 || p_power == 0){
                break; // Overflow or invalid
            }
            if(denominator % p_power != 0){
                break;
            }
            e += 1;
        }

        // Iterate over possible exponents starting from e
        for(int i = e; i < 100; ++i){
            ull p_pow_i = pow_safe(p, i);
            if(p_pow_i >= N + 1){
                break; // Overflow
            }

            ull new_n = current_n * p_pow_i;
            if(new_n > N){
                break; // Exceeds the limit
            }

            ull new_numerator = numerator * p_pow_i;
            if(new_numerator == 0){
                continue; // Prevent division by zero
            }

            // Compute (p^(i+1) - 1)
            ull p_pow_ip1 = pow_safe(p, i + 1);
            if(p_pow_ip1 >= N + 1 || p_pow_ip1 == 0){
                break; // Overflow or invalid
            }

            if(p_pow_ip1 < 1){
                break; // Invalid value
            }

            ull numerator_val = p_pow_ip1 - 1;
            ull denominator_val = p - 1;

            if(denominator_val == 0){
                continue; // Undefined, skip
            }

            // Ensure (p^(i+1) - 1) is divisible by (p - 1)
            if(numerator_val % denominator_val != 0){
                continue; // Not divisible, skip
            }

            ull factor = numerator_val / denominator_val;

            // Check for potential overflow in denominator * factor
            if(denominator > N / factor){
                break; // Exceeds the limit
            }

            ull new_denominator = denominator * factor;

            // Compute GCD of new_numerator and new_denominator
            ull k = std::gcd(new_numerator, new_denominator);
            if(k == 0){
                continue; // Undefined, skip
            }

            // Normalize the fractions by dividing by GCD
            ull final_n = new_n / k;
            ull final_numerator = new_numerator / k;
            ull final_denominator = new_denominator / k;

            // Push the new state onto the stack
            stk.emplace(final_n, final_numerator, final_denominator);
        }
    }

    // Output the final answer
    std::cout << "ans = " << sum_ans << "\n";
    return 0;
}

