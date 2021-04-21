//Author: Bruce Hart <bruce.hart@gmail.com>

// Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of numbers less than n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.

// n	Relatively Prime	φ(n)	n/φ(n)
// 2	1	1	2
// 3	1,2	2	1.5
// 4	1,3	2	2
// 5	1,2,3,4	4	1.25
// 6	1,5	2	3
// 7	1,2,3,4,5,6	6	1.1666...
// 8	1,3,5,7	4	2
// 9	1,2,4,5,7,8	6	1.5
// 10	1,3,7,9	4	2.5
// It can be seen that n=6 produces a maximum n/φ(n) for n ≤ 10.

// Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum.

#include <iostream>
#include <map>

#define MAX_N   10 //1000000

int main(int argc, char** argv)
{
    std::map<int, int> phi;

    for (int i=2; i <= MAX_N; i++)
        phi[i] = i-1;
    
    for (int j=2;j <= MAX_N; j++)
    {
        int m = 2*j;

        while (m <= MAX_N)
        {
            phi[m]--;
            m+=j;
        }
    }

    float max_ratio = 0.0;
    int maxK = 0;

    for(int k=2; k<= MAX_N; k++)
    {
        std::cout << k << " | " << phi[k] << " | " << (float)k/phi[k] << std::endl;
        if (k/phi[k] > max_ratio)
        {
            max_ratio = k/phi[k];
            maxK = k;
        }
    }

    std::cout << maxK << std::endl;
    std::cout << max_ratio << std::endl;

    return 0;
}