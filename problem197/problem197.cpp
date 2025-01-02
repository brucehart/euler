#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

double f(double x)
{
  return floor(pow(2.0, 30.403243784 - x*x)) * pow(10, -9);
}

int main(){    
    std::vector<double> uResults;
    double u = -1.0;
    double ep = pow(10, -15);
    int count = 0;
    
    while(true)
    {
        uResults.push_back(u);
        u = f(u);        
        
        count++;
        if (count > 1000) break;
    }

    std::cout << count << std::endl;
    std::cout << std::fixed << std::setprecision(9) << uResults[uResults.size() - 1] + uResults[uResults.size() - 2] << std::endl;
}