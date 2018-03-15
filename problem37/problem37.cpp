//Author: Bruce Hart <bruce.hart@gmail.com>
// The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
// Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
// NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <sstream>
#include <cstdlib>

#define MAX_N 	1000000

void removeMultiples(int p, int N, std::map<int, char>& isPrime)
{
	int c = 2*p;

	while (c <= N)
	{
		isPrime[c] = 0;
		c += p;
	}
}

std::vector<int> buildPrimeList(int N, std::map<int, char>& isPrime)
{	
	std::vector<int> pSet;
	int p = 2;	

	for (int i=2;i<N;i++)	
		isPrime[i] = 1;
	
	while (p <= N/2)
	{
		removeMultiples(p, N, isPrime);
		p++;
		while (isPrime[p] == 0 && p <= N) { p++; }
	}

	for (int i=0;i<N;i++)
	{
		if (isPrime[i] == 1)
			pSet.push_back(i);
	}

	return pSet;
}

int trunL(int n)
{
	std::stringstream ss;
	ss << n;
	return atoi(ss.str().substr(1).c_str());
}

int trunR(int n)
{
	return n/10;
}

bool isTPrime(int n, std::map<int, char>& isPrime)
{
	if (!isPrime[n]) return false;

	int left = trunL(n);

	while (left > 0)
	{
		if (!isPrime[left]) return false;
		left = trunL(left);
	}

	int right = trunR(n);

	while (right > 0)
	{
		if (!isPrime[right]) return false;
		right = trunR(right);
	}

	return true;
}


int main(int argc, char** argv)
{
	std::map<int, char> isPrime;
	auto primes = buildPrimeList(MAX_N, isPrime);

	int primeSum = 0;
	int count = 0;

	int i = 11;

	while (count < 11 && i < MAX_N)
	{
		if (isTPrime(i, isPrime))
		{
			count++;
			primeSum += i;
			//std::cout << i << "\n";
		}

		i += 2;
	}

	std::cout << primeSum << "\n";

	return 0;
}