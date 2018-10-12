//Author: Bruce Hart <bruce.hart@gmail.com>

// Prime square remainders
// Problem 123 
// Let pn be the nth prime: 2, 3, 5, 7, 11, ..., and let r be the remainder when (p_n−1)^n + (p_n+1)^n is divided by pn2.

// For example, when n = 3, p3 = 5, and 4^3 + 6^3 = 280 ≡ 5 mod 25.
// The least value of n for which the remainder first exceeds 10^9 is 7037.
// Find the least value of n for which the remainder first exceeds 10^10.

#include <iostream>
#include <vector>
#include <cstdlib>

#define MAX_R			10000000000

//From Problem 120, we learn that r = 2 for all even values of n and
//r = 2*a*n for odd values of n
//Approach -- Compute 2*a*n for all odd primes until the result > 10^9
std::vector<uint64_t> primes;

void nextOddPrime()
{
	uint64_t i = primes[primes.size()-1] + 1;
	bool primeFound = false;

	while (!primeFound)
	{
		primeFound = true;

		for (auto p: primes)
		{			
			if (i%p == 0) 
			{
				primeFound = false;			
				break;
			}

			if (p*p > i) break;
		}

		if (primeFound)
			primes.push_back(i);
		else
			i++;
	}

	if (primes.size()%2 == 0)
		nextOddPrime();
}

int main(int argc, char** argv)
{
	primes.push_back(2);
	primes.push_back(3);

	uint64_t r = 0;

	while (r < MAX_R)
	{		
		nextOddPrime();
		r = 2*primes.size()*primes[primes.size()-1];
	}

	std::cout << primes.size() << std::endl;
}