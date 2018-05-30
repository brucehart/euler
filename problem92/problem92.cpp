///Author: Bruce Hart <bruce.hart@gmail.com>

#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iostream>

#define MAX_N 		10*1000*1000

std::set<int> termN = {1, 89};
std::map<int, int> matches;

int squareSum(int n)
{
	int digitSum = 0;
	int d = 0;

	while(n > 0)
	{
		d = n%10;
		digitSum += d*d;
		n /= 10;
	}

	return digitSum;
}

int main(int argc, char** argv)
{
	std::for_each(termN.begin(), termN.end(), [&](const int &t){matches[t]= t;});

	int n = 1;
	int x = 0;
	std::set<int> chain;
	int count = 0;

	while (n <= MAX_N)
	{
		x = n;
		
		while (true)
		{
			if (matches[x] > 0){
				std::for_each(chain.begin(), chain.end(), [&](const int &c){matches[c] = matches[x];});
				goto nextN;
			}

			for (auto &t: termN){
				if (x == t){
					std::for_each(chain.begin(), chain.end(), [&](const int &c){matches[c] = x;});
					goto nextN;
				}
			}

			chain.insert(x);
			x = squareSum(x);				
		}

		nextN:
			chain.clear();
			n++;			
	}

	for_each(matches.begin(), matches.end(), [&](const std::pair<int,int> &m){if (m.second == 89) count++;});
	std::cout << count << "\n";
}