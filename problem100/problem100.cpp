//Author: Bruce Hart <bruce.hart@gmail.com>

// If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs, and 
//two discs were taken at random, it can be seen that the probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.

//The next such arrangement, for which there is exactly 50% chance of taking two blue discs at random, is a box containing 
//eighty-five blue discs and thirty-five red discs.

// By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs in total, determine the number of blue 
//discs that the box would contain.

#include <iostream>
#include <cmath>
#include <set>
#include <cstdint>

#define  MIN_TOTAL		1000000000000

int main(int argc, char** argv)
{
	int64_t blueD = 15;
	int64_t total = 21;
	int64_t tempBlue = blueD;
	int64_t tempTotal = total;	

	//(blue/total)*((blue-1)/(total-1)) = 0.5
	//iterative solution to a quadratic diophantine equation
	
	while (total <= MIN_TOTAL)
	{
		blueD = 3*tempBlue + 2*tempTotal - 2;
		total = 4*tempBlue + 3*tempTotal - 3;
		tempBlue = blueD;
		tempTotal = total;		
	} 
	

	std::cout << blueD << std::endl;
}