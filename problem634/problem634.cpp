//Author: Bruce Hart <bruce.hart@gmail.com>

// Numbers of the form a^2*b^3
// Problem 634 
// Define F(n) to be the number of integers x≤n that can be written in the form x=a^2*b^3, where a and b are integers not necessarily different and both greater than 1.

// For example, 32=2^2×2^3 and 72=3^2×2^3 are the only two integers less than 100 that can be written in this form. Hence, F(100)=2.

// Further you are given F(2×10^4)=130 and F(3×10^6)=2014.

// Find F(9×10^18).


#include <iostream>
#include <cmath>
#include <set>
#include <cstdint>

#define N 		2*std::pow(10,4)

int main(int argc, char** argv)
{	
	uint64_t a = 2;
	uint64_t b = 2;	
	uint64_t count = 0;
	uint64_t maxA = 0;
	double x = 0;
	double logN = std::log(N);
	std::set<uint64_t> matches;
	
	for (b = 2; 2.0*std::log(2)+3.0*std::log(b) <= logN; b++)
	{
		maxA = std::floor(std::exp(0.5*(logN-3*std::log(b))));
		count += maxA;
		std::cout << "b = " << b << " maxA = " << maxA << " count = " << count << std::endl;
	}	

	std::cout << count << std::endl;
}
