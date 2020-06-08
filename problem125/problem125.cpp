//problem125.cpp
// Author: Bruce Hart <bruce.hart@gmail.com>

// The palindromic number 595 is interesting because it can be written as the sum of consecutive squares: 6^2 + 7^2 + 8^2 + 9^2 + 10^2 + 11^2 + 12^2.

// There are exactly eleven palindromes below one-thousand that can be written as consecutive square sums, and the sum of these palindromes is 4164. 
// Note that 1 = 0^2 + 1^2 has not been included as this problem is concerned with the squares of positive integers.

// Find the sum of all the numbers less than 10^8 that are both palindromic and can be written as the sum of consecutive squares.

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdint.h>
#include <sstream>

#define SQRT_MAX_N	10000
#define MAX_N 		100000000

bool isPalindrome(uint64_t n)
{
	std::stringstream ss;
	ss << n;

	auto s = 0;
	auto e = ss.str().length()-1;

	while (ss.str()[s] == ss.str()[e])
		if (s++ >= e--) return true;
		
	return false;
}



int main(int argc, char** argv)
{
	std::set<uint64_t> palindromes;

	int i = 1;
	uint64_t sum = 0;
	uint64_t pSum = 0;

	while (i <= SQRT_MAX_N)
	{
		auto j = i;
		sum = j*j;
		j++;

		while (j <= SQRT_MAX_N)
		{
			sum += j*j;

			if (sum > 1 && sum < MAX_N && isPalindrome(sum))
				palindromes.insert(sum);
			else if (sum >= MAX_N)
				break;
			
			j++;
		}

		i++;
	}

	for (auto x: palindromes)
		pSum+= x;
	
	std::cout << pSum << std::endl;

	return 0;
}