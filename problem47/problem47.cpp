//Author: Bruce Hart <bruce.hart@gmail.com>
// The first two consecutive numbers to have two distinct prime factors are:

// 14 = 2 × 7
// 15 = 3 × 5

// The first three consecutive numbers to have three distinct prime factors are:

// 644 = 2² × 7 × 23
// 645 = 3 × 5 × 43
// 646 = 2 × 17 × 19.

// Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?


#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <sstream>
#include <cstdlib>
#include <set>

#define NUM_FACTORS		4
#define SEQ_LEN			4

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

int countUniqueFactors(int N, std::vector<int>& primeList)
{
	int factors = 0;
	int i = 0;

	while (i < primeList.size()-1 && primeList[i] <= N/2)
	{		
		if (N%primeList[i] == 0)		
			factors++;				

		i++;
	}

	return factors;
}

int main(int argc, char** argv)
{
	std::map<int, char> isPrime;
	auto primes = buildPrimeList(MAX_N, isPrime);

	int factorCount = 0;

	for(int i=3;i<MAX_N;i++)
	{
		if (countUniqueFactors(i, primes) == NUM_FACTORS)
			factorCount++;
		else
			factorCount = 0;

		if (factorCount == SEQ_LEN)
		{
			std::cout << (i-3);
			break;
		}

	}

	return 0;

}