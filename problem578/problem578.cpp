#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <deque>

typedef unsigned long long ull;
const ull N = 1000000; //10000000000000ULL; // 10^13

struct CountTask {
    int targetIdx;
    int maxPower;
    double remaining;     
};

// Function to generate primes up to max_limit using Sieve of Eratosthenes
std::vector<double> generate_primes(ull max_limit) {
    ull sieve_limit = max_limit;
    std::vector<bool> is_prime(sieve_limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ull i = 2; i * i <= sieve_limit; ++i) {
        if (is_prime[i]) {
            for (ull j = i * i; j <= sieve_limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    std::vector<double> primes;
    for (ull i = 2; i <= sieve_limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(std::log(i));
        }
    }
    return primes;
}


void incrementCount(std::vector<double>& primes, int targetIdx, int maxPower, double remaining, ull& count, std::deque<CountTask>& tasks)
{
    if (targetIdx >= primes.size()) return;

    int topExp = static_cast<int>(std::floor(remaining / primes[targetIdx]));  
    if (topExp < maxPower) return;

    if (topExp > maxPower)
        count += topExp - maxPower;

    for (int exp = maxPower; exp <= topExp; ++exp) {        
        if (targetIdx + 1 >= primes.size()) break;
        if (remaining - exp * primes[targetIdx] - (exp+1)*primes[targetIdx+1] < 0) break;             
        tasks.push_back(CountTask{targetIdx + 1, exp, remaining - exp * primes[targetIdx]});
    }
}


int main() {
    ull sqrtN = static_cast<ull>(std::sqrt(N)) + 1;
    std::vector<double> primes = generate_primes(sqrtN);
    ull count = 0;
    std::deque<CountTask> tasks;    

    for (int i = 0; i < primes.size(); ++i) {
        tasks.push_back(CountTask{i, 0, std::log(N)});
    }

    while (!tasks.empty()) {
        CountTask task = tasks.front();
        tasks.pop_front();
        incrementCount(primes, task.targetIdx, task.maxPower, task.remaining, count, tasks);
        std::cout << "Count: " << count << " Remaining: " << task.remaining << std::endl;
    }

    
    return 0;    
}

