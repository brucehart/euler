//problem230.cpp
// Author: Bruce Hart <bruce.hart@gmail.com>

// For any two strings of digits, A and B, we define F_A,B to be the sequence (A,B,AB,BAB,ABBAB,...) in which each term is the concatenation of the previous two.

// Further, we define D_A,B(n) to be the nth digit in the first term of F_A,B that contains at least n digits.

// Example:

// Let A=1415926535, B=8979323846. We wish to find D_A,B(35), say.

// The first few terms of FA,B are:
// 1415926535
// 8979323846
// 14159265358979323846
// 897932384614159265358979323846
// 14159265358979323846897932384614159265358979323846

// Then D_A,B(35) is the 35th digit in the fifth term, which is 9.

// Now we use for A the first 100 digits of π behind the decimal point:

// 14159265358979323846264338327950288419716939937510 
// 58209749445923078164062862089986280348253421170679

// and for B the next hundred digits:

// 82148086513282306647093844609550582231725359408128 
// 48111745028410270193852110555964462294895493038196 .

// Find ∑n = 0,1,...,17   10^n * D_A,B((127+19n)×7^n) .

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdint.h>

#define pi_A 	"1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
#define pi_B	"8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"

#define MAX_N	17

uint64_t termIndex(int n)
{
	//compute the formula defined in the problem
	//manually compute the 7^n term to keep it in int form
	uint64_t retVal = (127 + 19*n);

	for (int i=0;i<n;i++)
		retVal *= 7;

	return retVal;
}

char findSource(uint64_t n, const std::vector<uint64_t>& fib, const std::string& A, const std::string& B, int64_t seq = -1)
{
	//start by seeing if we are looking for an index defined in A or B
	if (seq == 0 && n <= A.size())
		return A[n-1];

	if (seq == 1 && n <= B.size())
		return B[n-1];

	int f = seq;

	//if we don't know which term to count back from yet, search for it
	if (seq == -1)
	{
		f = 0;
		while (fib[f] < n) f++;
	}

	//search iteratively backwards, removing previous term
	if (n > fib[f-2])
		return findSource(n - fib[f-2], fib, A, B, f-1);
	else
		//once we've locked in on the index, jump back to the A or B string and return the value in the next iteration
		return findSource(n, fib, A, B, f-2);

}

int main(int argc, char** argv)
{
	//initialize vectors for fibonacci sequence, index values
	//create an empty string where the results will be appended
	std::vector<uint64_t> fib;
	std::vector<uint64_t> nVal;
	std::string sum = "";

	//prestore the #defined numeric sequences for easy reference
	std::string A = std::string(pi_A);
	std::string B = std::string(pi_B);

	//create a vector of index values that we will be looking for
	for (int i=0;i<=MAX_N;i++)
	{
		nVal.push_back(termIndex(i));
	}

	fib.push_back(A.size());
	fib.push_back(B.size());
	
	while (fib[fib.size()-1] < nVal[nVal.size()-1])
	{
		fib.push_back(fib[fib.size()-2] + fib[fib.size()-1]);
	}

	for (int n = nVal.size()-1; n >= 0; n--)
	{
		sum += findSource(nVal[n], fib, A, B);				
	}

	std::cout << sum;

	return 0;
}