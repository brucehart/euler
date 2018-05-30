//Author: Bruce Hart <bruce.hart@gmail.com>

#include <string>
#include <iostream>
#include <algorithm>

#define MAX_N	1000000

std::string convertToBase14(int n)
{	
	std::string s = "";
	std::string digits = "0123456789abcd";

	while (n > 0)
	{
		s = digits[n%14]+s;
		n /= 14;
	}

	return s;
}

bool isSteadySquare(int n)
{
	std::string base   = convertToBase14(n);
	std::string square = convertToBase14(n*n);

	return std::equal(base.rbegin(), base.rend(), square.rbegin());
}

int main(int argc, char** argv)
{
	unsigned int digitSum = 0;	

	for (int i=1;i<=MAX_N;i++)
	{
		if (isSteadySquare(i))
		{			
			digitSum += i;

			std::cout << convertToBase14(i) << " : " << convertToBase14(i*i) << "\n";
		}
	}

	std::cout << convertToBase14(digitSum) << "\n";

	return 0;
}