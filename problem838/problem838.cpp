#include <iostream>
#include <set>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

static int N = 1000000;

std::vector<cpp_int> prime_factorization(cpp_int n){
    std::vector<cpp_int> factors;
    for(cpp_int i = 2; i <= n; i++){
        while(n % i == 0){
            factors.push_back(i);
            n /= i;
        }
    }
    return factors;
}

int main(){
    std::set<cpp_int> primes;
    cpp_int result = 1;

    for(int i = 3; i <= N; i+=10){
        std::cout << i << std::endl;
        std::vector<cpp_int> factors = prime_factorization(i);
        for(auto factor : factors){
            primes.insert(factor);
        } 
    }

    for(auto prime : primes){
        result *= prime;
    }   

    std::cout << result << std::endl;

    return 0;
}