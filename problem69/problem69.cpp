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
#include <cmath>

#define MAX_N   1000000

bool is_prime(int n)
{
	for (int i=2;i<=sqrt(n);i++)
	{
		if (n%i == 0)
			return false;
	}

	return true;
}

int next_prime(int start=1)
{
    int x = start;

    while(true)
    {
        if (is_prime(x)) return x;
        x++;
    }
}

int main(int argc, char** argv)
{
    int m = 1;
    int n = next_prime();

    while (m*n <= MAX_N)
    {
        m = m*n;
        n = next_prime(n+1);
    }

    std::cout << m << std::endl;
    return 0;
}