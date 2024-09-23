#include <iostream>
#include <set>
#include <cstdint>

std::set<int64_t> solutions;

void generateSolutions(int numSolutions, int64_t xi, int64_t yi)
{
    int n = 0;
    auto xPrev = xi;
    auto yPrev = yi;

    while (n < numSolutions)
    {
        xi = -9*xPrev - 4*yPrev - 14;
        yi = -20*xPrev - 9*yPrev - 28;

        if (xi > 0){
            solutions.insert(xi);
            n++;
        }

        xPrev = xi;
        yPrev = yi;
    }
}

int main(){
    //use intial values and functions from https://www.alpertron.com.ar/QUAD.HTM
    generateSolutions(30, 2, -7);
    generateSolutions(30, 0, -1);
    generateSolutions(30, 0, 1);
    generateSolutions(30, -4, 5);
    generateSolutions(30, -3, 2);
    generateSolutions(30, -3, -2);

    if (solutions.size() >= 30) {
        int64_t sum = 0;
        auto it = solutions.begin();
        for (int i = 0; i < 30; ++i, ++it) {
            sum += *it;
        }
        std::cout << sum << std::endl;
    }
    
    return 0;
}