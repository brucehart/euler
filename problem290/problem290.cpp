#include <iostream>
#include <cmath>


int sumOfDigits(unsigned int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

bool checkValue(unsigned int n) {
    int sumN = sumOfDigits(n);
    int sum137N = sumOfDigits(137 * n);
    return sumN == sum137N;
}

unsigned long long convertValue(unsigned int n)
{
    unsigned long long m = 1;
    unsigned long long v = 0;
    for(int i = 0; i < 18; i++){
        if (n & (1 << i))
           v += m;
        m *= 9;
    }
    return v;
}

unsigned long long computeSum() {    
    unsigned long long sum = 0;

    for (int i = 0; i <= (pow(2,18) -1); i++) {        
       
        auto v = convertValue(i);
        if (v > 1e18) continue;

         if (i % 1000 == 0)
            std::cout << i << " | " << v << std::endl;

        if (checkValue(v)) {
            sum += v;
        }
    }

    return sum;
}

int main(){
    std::cout << computeSum() << std::endl;
    return 0;
}