#include <iostream>
#include <cmath>

long long generatePythagoreanTriples(long long limit) {
    long long count = 1;

    int ctr = 0;

    // Generate Pythagorean triples using the formula
    for (long long m = 2; ; ++m) {
        for (long long n = 1; n < m; ++n) {
            if ((m - n) % 2 == 1 && std::__gcd(m, n) == 1) {
                long long a = m * m - n * n;
                long long b = 2 * m * n;
                long long c = m * m + n * n;

                //sort a, b, c
                if (a > b) std::swap(a, b);
                if (b > c) std::swap(b, c);
                if (a > b) std::swap(a, b);

                if (a + b + c > limit) {
                    return count;
                }

                long long tile_size = std::abs(b - a);
                
                // Check if the tile size is a multiple of c
                if (c % tile_size == 0) {
                    count += (limit - 1) / (a + b + c);                    
                }
            }
        }
    }

    return count;
}

int main(){
    long long limit = 100000000;
    long long count = generatePythagoreanTriples(limit);
    
    std::cout << count << std::endl;
    
    return 0;
}

