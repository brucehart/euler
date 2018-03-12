//Author: Bruce Hart <bruce.hart@gmail.com>
// We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
// What is the largest n-digit pandigital prime that exists?

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <stdlib.h>

std::string pdBase(int n)
{
	std::string base = "123456789";

	base = base.substr(0,n);

	std::sort(base.begin(), base.end());
	std::reverse(base.begin(), base.end());	
	return base;
}



bool isPrime(int n)
{
	for (int i=2;i<sqrt(n);i++)
	{
		if (n%i == 0)
			return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	int n = 9;
	
	while(n > 1)
	{
		std::string seq = pdBase(n);

		do
		{
			if (isPrime(atoi(seq.c_str())))
			{
				std::cout << seq << "\n";
				return 0;
			}

		} while(std::prev_permutation(seq.begin(), seq.end()));

		n--;
	}

	std::cout << "Prime not found.\n";
	return 0;
}