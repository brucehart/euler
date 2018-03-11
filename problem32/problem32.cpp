//Author: Bruce Hart <bruce.hart@gmail.com>
// Pandigital products
// Problem 32 
// We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

// The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

// Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

// HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

#include <iostream>
#include <set>

#define MAX_A		2000

void pdCount(int x, int* count)
{
	while (x > 0)
	{
		count[x%10]++;
		x = x/10;
	}
}

bool isPandigital(int a, int b = -1, int c = -1)
{
	int count[10];
	int sum = 0;

	for (int j=0;j<10;j++) count[j] = 0;

	pdCount(a, count);
	pdCount(b, count);
	pdCount(c, count);

	if (count[0] > 0) return false;

	for (int i=1;i<=9;i++)
	{
		if (count[i] != 1) return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	std::set<int> prod; 
	int c;	
	int sum = 0;

	for (int a = 1; a < MAX_A; a++)
	{
		for (int b = 1; b < MAX_A; b++)
		{
			c = a*b;
			if (isPandigital(a,b,c))
			{
				prod.insert(c);				
			}
		}
	}

	for (auto v: prod)
	{
		sum += v;
	}

	std::cout << sum << "\n";

	return 0;
}