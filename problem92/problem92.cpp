///Author: Bruce Hart <bruce.hart@gmail.com>

#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iostream>

#define MAX_N 		10*1000*1000

std::set<int> termN = {1, 89};
std::map<int, std::set<int>> matches;

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
	std::for_each(termN.begin(), termN.end(), [&](const int &t){matches[t].insert(t);});

	int n = 1;
	int x = 0;
	std::set<int> chain;

	while (n <= MAX_N)
	{
		x = n;
		
		while (true)
		{
			for (auto &m: matches){				
				if (x == m.first || m.second.find(x) != m.second.end()){
					std::for_each(chain.begin(), chain.end(), [&](const int &c){m.second.insert(c);});
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

	std::cout << matches[89].size() << "\n";
}