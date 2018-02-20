//problem67.cpp
// Author: Bruce Hart <bruce.hart@gmail.com>

// By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

// 3
// 7 4
// 2 4 6
// 8 5 9 3

// That is, 3 + 7 + 4 + 9 = 23.

// Find the maximum total from top to bottom in triangle.txt (right click and 'Save Link/Target As...'), a 15K text file containing a triangle with one-hundred rows.

// NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route to solve this problem, as there are 299 altogether! If you could check one trillion (1012) routes every second it would take over twenty billion years to check them all. There is an efficient algorithm to solve it. ;o)

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <cmath>
#include <vector>
#include <algorithm>

std::vector<int> maxSum(std::vector<int>& lastRow, std::vector<int>& data)
{
	std::vector<int> sums;
	int row = lastRow.size()+1;
	int s = 0;

	for (int i=0;i<row;i++)
		s += i;

	if (row == 1)	
		sums.push_back(data[0]);	
	else
	{
		for (int j=0;j<row;j++)
		{
			if (j == 0)
				sums.push_back(lastRow[j] + data[s+j]);
			else if (j < (row-1))			
				sums.push_back(std::max(lastRow[j-1], lastRow[j]) + data[s+j]);
			else
				sums.push_back(lastRow[j-1] + data[s+j]);
		}
	}

	return sums;
}

void readFile(std::string path, std::vector<int>& data)
{
	std::string line;
	std::ifstream f(path);
	int v;

	while (!f.eof())
	{
		f >> v;
		data.push_back(v);
	}

	f.close();
}

int main(int argc, char** argv)
{
	std::vector<int> data;
	readFile("triangle.txt", data);

	std::vector<int> sums;

	while (sums.size() < 100)
	{
		sums = maxSum(sums, data);		
	}

	auto mIdx = std::max_element(sums.begin(), sums.end());
	std::cout << sums[std::distance(sums.begin(), mIdx)] << "\n";

	return 0;
}