//Author: Bruce Hart <bruce.hart@gmail.com>
// It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

// 9 = 7 + 2×1^2
// 15 = 7 + 2×2^2
// 21 = 3 + 2×3^2
// 25 = 7 + 2×3^2
// 27 = 19 + 2×2^2
// 33 = 31 + 2×1^2

// It turns out that the conjecture was false.
// What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?


#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cstdint>

#define MAX_N 	100000
#define MAX_C	100000
#define MAX_S	10000

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

int main(int argc, char** argv)
{	
	std::map<int, char> isPrime;
	auto primes = buildPrimeList(MAX_N, isPrime);

	std::map<int, char> doubleSq;

	for (int i=0;i<MAX_S;i++)
		doubleSq[2*i*i] = 1;
	

	uint32_t c = 9;

	while (c < MAX_C)
	{
		if (!isPrime[c])
		{
			bool match = false;

			for (int j=0;j<primes.size();j++)
			{
				if (primes[j] > c) break;

				if (doubleSq[c - primes[j]] == 1)
				{
					match = true;
					break;
				}
			}

			if (match == false)
			{
				std::cout << c << "\n";
				return 0;
			}

		}
		c += 2;
	}


	return 0;
}