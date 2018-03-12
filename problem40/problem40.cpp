//Author: Bruce Hart <bruce.hart@gmail.com>

// Champernowne's constant
// Problem 40 

// An irrational decimal fraction is created by concatenating the positive integers:

// 0.123456789101112131415161718192021...

// It can be seen that the 12th digit of the fractional part is 1.

// If dn represents the nth digit of the fractional part, find the value of the following expression.

// d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#define MAX_D 1000000
#define MAX_I 500000

int main(int argc, char** argv)
{
	std::stringstream ss;

	int i = 1;

	while (i < MAX_I)
	{
		ss << i;
		i++;
	}

	std::string champ = ss.str();

	unsigned int mult = 1;
	int idx = 1;

	while (idx <= MAX_D)
	{
		mult *= (champ[idx-1]-'0');		
		idx *= 10;
	}

	std::cout << mult << "\n";
}