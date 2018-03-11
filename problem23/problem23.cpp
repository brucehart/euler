//Author: Bruce Hart <bruce.hart@gmail.com>
// Non-abundant sums
// Problem 23 
// A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

// A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

// As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

// Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

#include <iostream>
#include <set>

#define MAX_N 	28123

int divisorSum(int N)
{
	int sum = 0;

	for (int i=N-1;i>=1;i--)
	{
		if (N%i == 0)
			sum += i;
	}

	return sum;
}

int main(int argc, char** argv)
{
	std::set<int> abundantN;
	std::set<int> abundantSum;
	long long int sum = 0;

	for (int i=1;i<MAX_N;i++)
	{
		if (divisorSum(i) > i)
		{
			abundantN.insert(i);			
		}

		abundantSum.insert(i);
	}


	for (auto x = abundantN.begin();x != abundantN.end();x++)
	{
		for (auto y = x; y != abundantN.end();y++)
		{
			abundantSum.erase(*x+*y);
		}
	}

	int count = 1;
	for (auto s: abundantSum)
	{
		sum += s;
		count++;
	}

	std::cout << sum << "\n";

	return 0;
}