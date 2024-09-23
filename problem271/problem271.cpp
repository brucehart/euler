#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

int main(){
    cpp_int singlePrimes = 2*3*5*11*17*23*29*41;
    cpp_int multiPrimes = 7*13*19*31*37*43;
    cpp_int total = singlePrimes * multiPrimes;

    cpp_int sum = 0;
    cpp_int x = singlePrimes + 1;

    while (x < total)
    {
        if (x*x*x % multiPrimes == 1){
            sum += x;
        }

        x += singlePrimes;
    }

    std::cout << sum << std::endl;
    return 0;
}