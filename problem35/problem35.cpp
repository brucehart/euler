// Author: Bruce Hart <bruce.hart@gmail.com>
// The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
// There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
// How many circular primes are there below one million?

#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>

#define MAX_N	1000000

bool isPrime(int n)
{
	for (int i=2;i<=sqrt(n);i++)
	{
		if (n%i == 0)
			return false;
	}

	return true;
}


bool isCircularPrime(int n)
{
	std::stringstream ss;
	ss << n;

	std::string s = ss.str();

	for (int i = 0;i<s.size();i++)
	{
		std::string sp = s.substr(i, s.size()-i);
		sp += s.substr(0, i);

		if (!isPrime(atoi(sp.c_str())))
			return false;
	}
	
	return true;
}

int main(int argc, char** argv)
{
	int count = 0;

	for (int i=2;i<MAX_N;i++)
	{
		if (isCircularPrime(i))
		{
			count++;
			//std::cout << i << "\n";
		}
	}

	std::cout << count << "\n";

	return 0;
}