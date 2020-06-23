//Author: Bruce J. Hart <bruce.hart@gmail.com>

// We define an S-number to be a natural number, n, that is a perfect square and its square root can be obtained by splitting the decimal representation of n uint64_to 2 or more numbers then adding the numbers.

// For example, 81 is an S-number because 81−−√=8+1.
// 6724 is an S-number: 6724−−−−√=6+72+4.
// 8281 is an S-number: 8281−−−−√=8+2+81=82+8+1.
// 9801 is an S-number: 9801−−−−√=98+0+1.

// Further we define T(N) to be the sum of all S numbers n≤N. You are given T(10^4)=41333.

// Find T(10^12)

#include <iostream>
#include <cmath>
#include <set>
#include <cstdint>
#include <math.h>

#define MAX_N		1000000000000
#define SQRT_MAX_N  1000000

int numDigits(int x)
{
	auto nD = ceil(log10((double)x));
	return (int)nD;
}

uint64_t evalSum(uint64_t x, uint64_t digitMask)
{

	uint64_t sum = 0;
	uint64_t d = 0;
	uint64_t c = 0;
	auto nD = numDigits(x);

	if (nD == 1) return x;

	for(auto i=0;i<nD;i++)
	{
		d += (x % 10)*pow(10,c++);

		if ((digitMask & (1 << (i-0))) > 0)
		{
			sum += d;
			d = 0;
			c = 0;
		}
				
		x /= 10;
		
	}

	sum += d;

	return sum;
}

bool isSplitSum(uint64_t target, uint64_t squareRoot)
{
	uint64_t nD = numDigits(target);

	if (nD < 2) return false;

	for(uint64_t i=0;i<=(2<<(nD-1));i++)
	{
		if (evalSum(target, i) == squareRoot)
			return true;		
	}

	return false;

}



int main(int argc, char** argv)
{
	uint64_t sum =  0;

	std::cout << evalSum(10000, 2) << std::endl;

	for (uint64_t i = 1; i <= 100; i++)
	{
		if (isSplitSum(i*i, i)) 
			sum += i*i;
	}

	std::cout << "81: " << isSplitSum(81,9) << std::endl;
	std::cout << "6724: " << isSplitSum(6724,82) << std::endl;
	std::cout << "8281: " << isSplitSum(8281,91) << std::endl;
	std::cout << "9801: " << isSplitSum(9801,99) << std::endl;
	std::cout << "10000: " << isSplitSum(10000,100) << std::endl;
	

	std::cout << sum << std::endl;

	return 0;
}