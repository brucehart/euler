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

#define MAX_N   1000000

unsigned int gcd(unsigned int u, unsigned int v)
{
    // Base cases
    // gcd(n, n) = n
    if (u == v)
        return u;
    
    //  Identity 1: gcd(0, n) = gcd(n, 0) = n
    if (u == 0)
        return v;
    if (v == 0)
        return u;

    if (u & 1) { // u is odd
        if (v % 2 == 0) // v is even
            return gcd(u, v / 2); // Identity 3
        // Identities 4 and 3 (u and v are odd, so u-v and v-u are known to be even)
        if (u > v)
            return gcd((u - v) / 2, v);
        else
            return gcd((v - u) / 2, u);
    } else { // u is even
        if (v & 1) // v is odd
            return gcd(u / 2, v); // Identity 3
        else // both u and v are even
            return 2 * gcd(u / 2, v / 2); // Identity 2
    }
}

int main(int argc, char** argv)
{
    std::map<int, int> phi;

    float max_ratio = 0.0001;
    float target = 0.0;
    int maxK = 0;

    for (int i=2;i<=MAX_N;i++)
    {
        phi[i] = 1;
        target = i/max_ratio;

        for (int j=2;j<i;j++)
        {
            if (gcd(j,i) == 1) phi[i]++;
            if (phi[i] > target) break;
        }

        if (i % 1000 == 0) std::cout << i << std::endl;

        if ((float)i/phi[i] > max_ratio) 
        {
            maxK = i;
            max_ratio = (float)i/phi[i];
        }
    }

    

    for(int k=2; k<= MAX_N; k++)
    {
        //std::cout << k << " | " << phi[k] << " | " << (float)k/phi[k] << std::endl;
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