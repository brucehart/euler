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
	uint64_t x = 0;
	std::set<uint64_t> matches;
	
	while (true)
	{
		while (x = pow(a,2)*pow(b,3), x <= N)
		{		
			if (matches.count(x) == 0)
			{				
				matches.insert(x);				
				//std::cout << matches.size() << " : " << a << "^2*" << b << "^3" << "=" << x << std::endl;
			}			

			b++;
		}

		b=2;
		a++;

		if (pow(a,2)*pow(b,3) > N) break;
	}

	std::cout << matches.size() << std::endl;
}
