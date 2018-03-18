//Author: Bruce Hart <bruce.hart@gmail.com>

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <sstream>

#define NUM_SPACES			40
#define MATRIX_ITERATIONS	10

const std::vector<double> diceHistogram()
{
	const std::vector<double> h = {0.0, 0.0, 1.0/16.0, 2.0/16.0, 3.0/16.0, 4.0/16.0, 3.0/16.0, 2.0/16.0, 1.0/16.0};	
	return h;
}

const double threeDoubles() 
{
	double p = (1.0/6.0)*(1.0/6.0)*(1.0/6.0);
	return p;
}

std::string findTopThree(std::vector<double> a)
{
	std::vector<std::pair<double, int>> v;
	std::stringstream ss;

	for (int i=0;i<a.size();i++)
	{
		v.push_back(std::make_pair(a[i], i));
	}

	std::sort(v.begin(), v.end(), [](const std::pair<double, int>& a, const std::pair<double, int>& b)-> bool {return a.first > b.first;});

	for (int i=0;i<3;i++)
	{
		if (v[i].second < 10)
			ss << "0";

		ss << v[i].second;
	}	

	return ss.str();
}

std::vector<std::vector<double>> squareMatrix(std::vector<std::vector<double>>& m)
{
	std::vector<std::vector<double>> m2;
	m2.resize(m.size());

	for (int i=0;i<NUM_SPACES;i++)
	{
		m2[i].resize(m[i].size());
	}

	for (int i=0;i<NUM_SPACES;i++)
	{
		for (int j=0;j<NUM_SPACES;j++)
		{
			m2[i][j] = 0.0;

			for (int k=0;k<NUM_SPACES;k++)
			{
				m2[i][j] += m[i][k]*m[k][j];
			}
		}
	}

	return m2;
}

void readSpaceFile(std::map<std::string, int>& spaces)
{
	std::ifstream inFile;
	inFile.open("spaces.txt");
	std::string space;
	int i = 0;

	while(inFile >> space)	
		spaces[space] = i++;

	inFile.close();
}

void buildMatrix(std::vector<std::vector<double>>& m, std::map<std::string, int>& spaces)
{
	auto dh = diceHistogram();
	std::string ccCards[] = {"CC1", "CC2", "CC3"};
	std::string chCards[] = {"CH1", "CH2", "CH3"};
	std::string nextR[] = {"R2", "R3", "R1"};
	std::string nextU[] = {"U1", "U2", "U1"};
	std::string backThree[] = {"T1", "D3", "CC3"};

	for (int i=0;i < NUM_SPACES; i++)
	{
		for (int j=0;j<dh.size();j++)			
				m[i][(j+i)%40] += (1-threeDoubles())*dh[j];	

		m[i][spaces["JAIL"]] += threeDoubles();
		m[i][spaces["JAIL"]] += m[i][spaces["G2J"]];
		m[i][spaces["G2J"]] = 0.0;

		for (int j=0;j<3;j++)
		{
			auto ch = chCards[j];

			m[i][spaces["JAIL"]] += m[i][spaces[ch]]*(1.0/16.0);
			m[i][spaces["GO"]] += m[i][spaces[ch]]*(1.0/16.0);
			m[i][spaces["C1"]] += m[i][spaces[ch]]*(1.0/16.0);
			m[i][spaces["E3"]] += m[i][spaces[ch]]*(1.0/16.0);
			m[i][spaces["H2"]] += m[i][spaces[ch]]*(1.0/16.0);
			m[i][spaces["R1"]] += m[i][spaces[ch]]*(1.0/16.0);
			m[i][spaces[nextR[j]]] += m[i][spaces[ch]]*(2.0/16.0);
			m[i][spaces[nextU[j]]] += m[i][spaces[ch]]*(1.0/16.0);
			m[i][spaces[backThree[j]]] += m[i][spaces[ch]]*(1.0/16.0);
			
			m[i][spaces[ch]] *= (6.0/16.0);
		}

		for (auto cc: ccCards)
		{
			m[i][spaces["JAIL"]] += m[i][spaces[cc]]*(1.0/16.0);
			m[i][spaces["GO"]] += m[i][spaces[cc]]*(1.0/16.0);
			m[i][spaces[cc]] *= (14.0/16.0);
		}

	}
}

int main(int argc, char** argv)
{
	std::vector<std::vector<double>> m;
	std::map<std::string, int> spaces;	
	readSpaceFile(spaces);

	m.resize(NUM_SPACES);

	for(int i=0;i<NUM_SPACES;i++)
	{
		m[i].resize(NUM_SPACES);
	}

	buildMatrix(m, spaces);

	for (int i=0;i<MATRIX_ITERATIONS;i++)
	{
		m = squareMatrix(m);
	}

	std::cout << findTopThree(m[0]);

	return 0;
}