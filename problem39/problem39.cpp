// Author: Bruce Hart <bruce.hart@gmail.com>

// If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
// {20,48,52}, {24,45,51}, {30,40,50}
// For which value of p ≤ 1000, is the number of solutions maximised?

#include <iostream>
#include <cstring>
#include <map>
#include <cmath>

#define P_MAX       1000

int main(int argc, char** argv)
{
    std::map<int, int> pCount;
    int c;

    int max = 0;
    int maxIdx = 0;
  

    for (int a=1;a<P_MAX-1;a++)
    {
        for (int b=1;b<P_MAX-1;b++)
        {
            c = floor(sqrt(a*a + b*b));
            
            if (c*c == (a*a + b*b))
                pCount[a+b+c] += 1;                            
        }
    }
    
    for (int i=1;i<=P_MAX;i++)
    {        
        if (pCount[i] > max)
        {
            max = pCount[i];
            maxIdx = i;
        }
    }

    std::cout << maxIdx << "\n";

    return 0;
}