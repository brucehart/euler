//Author: Bruce Hart <bruce.hart@gmail.com>

#include <iostream>
#include <vector>
#include <map>
#include <cstdint>

#define MAX_N 1000000

void removeMultiples(uint32_t p, uint32_t N, std::map<uint32_t, uint8_t>& isPrime)
{
	uint32_t c = 2*p;

	while (c <= N)
	{
		isPrime[c] = 0;
		c += p;
	}
}

std::vector<uint32_t> buildPrimeList(uint32_t N, std::map<uint32_t, uint8_t>& isPrime)
{	
	std::vector<uint32_t> pSet;
	uint32_t p = 2;	

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
	std::vector<uint32_t> primes;
	std::map<uint32_t, uint8_t> isPrime;

	uint32_t longestSum = 0;
	uint32_t longestPrimeSum = 0;
	uint32_t j;
	uint64_t sum;

	primes = buildPrimeList(MAX_N, isPrime);
	
	for (uint32_t i=0;i<primes.size();i++)
	{
		j = i;
		sum = 0;

		while (sum < MAX_N && j < primes.size())
		{
			sum += primes[j++];

			if (isPrime[sum] && (j-i+1) > longestSum)
			{
				longestSum = (j-i+1);
				longestPrimeSum = sum;
			}
		}
	}

	//std::cout << longestSum << " : " << longestPrimeSum << "\n";
	std::cout << longestPrimeSum << "\n";

	return 0;
}