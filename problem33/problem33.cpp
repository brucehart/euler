//Author: Bruce Hart <bruce.hart@gmail.com>
// The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.
// We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
// There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.
// If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

void getDigits(const int num, const int den, int& nA, int& nB, int& dA, int& dB)
{
	nA = (num/10) % 10;
	nB = num%10;
	dA = (den/10) % 10;
	dB = den%10;
}

bool trivialCase(const int num, const int den)
{
	return ((num%10 == 0) && (den%10 == 0));
}

void reduceFrac(int& num, int& den)
{
	int fact = den;

	while (fact > 1)
	{
		if (den % fact == 0 && num%fact == 0)
		{
			den = den/fact;
			num = num/fact;
			fact = den;
		}
		else
		{
			fact--;
		}
	}
}

int main(int argc, char** argv)
{
	int nA, nB, dA, dB;
	int totalNum = 1;
	int totalDen = 1;

	std::vector<int> numMatch;
	std::vector<int> denMatch;

	for (int den = 10; den <= 99; den++)
	{
		for (int num = 10;num<den;num++)
		{
			if (trivialCase(num, den)) continue;

			getDigits(num, den, nA, nB, dA, dB);

			float ratio = (float)num/float(den);

			int n1;
			int d1;

			if (nA == dA)
			{
				n1 = nB;
				d1 = dB;				
			}
			else if (nA == dB)
			{
				n1 = nB;
				d1 = dA;
			}
			else if (nB == dB)
			{
				n1 = nA;
				d1 = dA;
			}
			else if (nB == dA)
			{
				n1 = nA;
				d1 = dB;
			}
			else
				continue;

			if (d1 > 0 && fabs((float)n1/(float)d1 - ratio) < 0.0001)
			{
				//std::cout << n1 << "/" << d1 << " = " << num << "/" << den << "\n";
				numMatch.push_back(n1);
				denMatch.push_back(d1);
			}

		}
	}

	for (int i=0;i<numMatch.size();i++)
	{
		totalNum *= numMatch[i];
		totalDen *= denMatch[i];
	}

	//std::cout << totalNum << "/" << totalDen << "\n";

	reduceFrac(totalNum, totalDen);

	std::cout << totalNum << "/" << totalDen << "\n";

	return 0;
}