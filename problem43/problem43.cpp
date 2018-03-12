//Author: Bruce Hart <bruce.hart@gmail.com>
// The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

// Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

// d2d3d4=406 is divisible by 2
// d3d4d5=063 is divisible by 3
// d4d5d6=635 is divisible by 5
// d5d6d7=357 is divisible by 7
// d6d7d8=572 is divisible by 11
// d7d8d9=728 is divisible by 13
// d8d9d10=289 is divisible by 17
// Find the sum of all 0 to 9 pandigital numbers with this property.

#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h> 
#include <gmp.h>

bool checkSubStr(std::string& pd, int idx, int len, int div)
{
	std::string s = pd.substr(idx, len);
	int val = atoi(s.c_str());

	if (val%div == 0)
		return true;
	else
		return false;
}

bool checkRules(std::string pd)
{
	std::vector<int> idx = {1,2,3,4,5,6,7};
	std::vector<int> len = {3,3,3,3,3,3,3};
	std::vector<int> div = {2,3,5,7,11,13,17};

	for (int i=0;i<idx.size();i++)
	{
		if (checkSubStr(pd, idx[i], len[i], div[i]) == false)
			return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	std::string pd = "0123456789";
	mpz_t pdSum, val;
	mpz_init(pdSum);
	mpz_init(val);

	do 
	{
		if (checkRules(pd))
		{
			mpz_set_ui(val, atoi(pd.c_str()));
			mpz_add(pdSum, pdSum, val);						
		}

	} while(std::next_permutation(pd.begin(), pd.end()));

	char buffer[100];
	mpz_set_str(pdSum, buffer, 10);

	std::cout << buffer << "\n";

	return 0;
}