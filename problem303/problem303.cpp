//Author: Bruce Hart <bruce.hart@gmail.com>

// Multiples with small digits
// Problem 303 
// For a positive integer n, define f(n) as the least positive multiple of n that, written in base 10, uses only digits ≤ 2.
// Thus f(2)=2, f(3)=12, f(7)=21, f(42)=210, f(89)=1121222.
// Also, sum[n=1..100] f(n)/n = 11363107.
// Find sum[n=1..10000] f(n)/n .

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

#define MAX_N		10000

uint64_t getNextMultiple(uint64_t m)
{
	uint64_t factor = 10;

	while (m % factor == 2*(factor/10))
	{
		m -= 2*(factor/10);
		factor *= 10;
	}

	m += (factor/10);	
	return m;
}

int main(int argc, char** argv)
{
	uint64_t m = 2;
	std::vector<uint64_t> mult(MAX_N+1, 0);
	std::vector<uint32_t> missing;
	std::vector<uint32_t> erase;
	int matchCount = 0;
	uint64_t sum = 0;

	for (int i=2;i<=MAX_N;i++)
		missing.push_back(i);

	mult[1] = 1;
	sum += 1;
	matchCount++;

	//special case for value 9999 (takes too long to generate)
	//for n of the form 9999, the least positive multiple is 1 repeated num_digits times follow by 2 repeated 4*num_digits times
	mult[9999] = 11112222222222222222UL;	
	missing.erase(missing.begin() + missing.size()-2);
	matchCount++;
	sum += mult[9999]/9999;

	while(matchCount < MAX_N)
	{
		for (int i=0;i<missing.size();i++)
		{
			if (m % missing[i] == 0)
			{
				mult[missing[i]] = m;
				erase.push_back(i);
				matchCount++;
				sum += m/missing[i];
			}
		}

		for (int i=erase.size()-1;i>=0;i--)		
			missing.erase(missing.begin()+erase[i]);
		
		erase.clear();

		m = getNextMultiple(m);
	}

	std::cout << sum << std::endl;
}