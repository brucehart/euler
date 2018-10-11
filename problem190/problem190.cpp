//Author: Bruce J. Hart <bruce.hart@gmail.com>

// Maximising a weighted product
// Problem 190 
// Let Sm = (x1, x2, ... , xm) be the m-tuple of positive real numbers with x1 + x2 + ... + xm = m for which Pm = x1 * x2^2 * ... * xm^m is maximised.

// For example, it can be verified that [P10] = 4112 ([ ] is the integer part function).

// Find Σ[Pm] for 2 ≤ m ≤ 15.

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#define  M_START		2
#define  M_END			15
#define  DELTAS			{0.01, 0.001, 0.0001, 0.00001}
#define  ALPHA			100


double computeP(std::vector<double> S)
{
	double P = 1.0;

	for (int n=1;n<=S.size();n++)
	{
		P *= pow(S[n-1],(double)n);
	}

	return P;
}


double findMaxP(int m)
{
	std::vector<double> S;
	std::vector<double> S_new;
	std::vector<double> deltas = DELTAS;

	std::default_random_engine rand;
	std::uniform_int_distribution<int> dist(0, m-1);
	int addIdx, subIdx;

	double maxP = 0;
	double newP;

	int missCount = 0;

	for (int i=0;i<m;i++)
		S.push_back(1.0);

	S_new.resize(S.size());

	maxP = computeP(S);

	for (auto d: deltas)
	{
		while (missCount < ALPHA)
		{
			std::copy(S.begin(), S.end(), S_new.begin());
			
			addIdx = dist(rand);
			subIdx = dist(rand);
	
			if (S_new[subIdx] > d)
			{
				S_new[addIdx] += d;
				S_new[subIdx] -= d;
			}

			newP = computeP(S_new);

			if (newP > maxP)
			{
				maxP = newP;
				std::copy(S_new.begin(), S_new.end(), S.begin());
				missCount = 0;
			}
			else
			{
				missCount++;
			}
		}

		missCount = 0;
	}

	return maxP;
}



int main(int argc, char** argv)
{

	double maxP;
	int maxPSum = 0;

	int attempts = 0;
	double P = 0.0;

	for (int m = M_START; m <= M_END; m++)
	{
		maxP = findMaxP(m);
		maxPSum += floor(maxP);				
	}

	std::cout << maxPSum;
}