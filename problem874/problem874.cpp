#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

std::vector<int> generatePrimes(int n) {
    std::vector<int> primes;
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; primes.size() < n; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (int multiple = 2 * p; multiple <= n; multiple += p) {
                is_prime[multiple] = false;
            }
        }
    }

    return primes;
}

int main(){
    cpp_int max_sum = 0;        
    auto primeList = generatePrimes(7000);
    std::cout << primeList.size() << std::endl;
    primeList = generatePrimes(primeList[6999]);
    std::cout << primeList.size() << std::endl;

    std::vector<int> a(primeList.size(), 6999);

    auto sum_a = std::accumulate(a.begin(), a.end(), 0);

    std::cout << sum_a << " % 7000 = " << sum_a % 7000 << std::endl;
    a[0] -= sum_a % 7000;

    sum_a = std::accumulate(a.begin(), a.end(), 0);
    std::cout << sum_a << " % 7000 = " << sum_a % 7000 << std::endl;

    for(int i = 0; i < primeList.size(); i++)
    {
        max_sum += primeList[a[i]];
    }

    std::cout << max_sum - (max_sum % 7000) << std::endl;
    
    return 0;
}