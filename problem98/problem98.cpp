//Author: Bruce Hart <bruce.hart@gmail.com>

// By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form a square number: 1296 = 36^2. What is remarkable is that, by using the same digital substitutions, the anagram, RACE, also forms a square number: 9216 = 96^2. We shall call CARE (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted, neither may a different letter have the same digital value as another letter.
// Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, find all the square anagram word pairs (a palindromic word is NOT considered to be an anagram of itself).
// What is the largest square number formed by any member of such a pair?
// NOTE: All anagrams formed must be contained in the given text file.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <sstream>
#include <utility>
#include <map>

#define FILE_PATH 		"words.txt"
#define MAX_SQUARE		1000000000000000

void readFile(std::vector<std::string>& words)
{
	std::string s;
	char c;

	std::fstream file(FILE_PATH, std::ios::in);

	while (!file.eof())
	{
		file >> c;

		if (c == '"') 
			continue;
		else if (c == ',')
		{
			words.push_back(s);
			s = "";
		}
		else
			s.push_back(c);
	}	
}

void sortWords(const std::vector<std::string>& words, std::vector<std::string>& sorted)
{
	sorted.clear();

	for (auto w: words)
	{
		auto x = w;
		std::sort(x.begin(),x.end());
		sorted.push_back(x);
	}
}

std::vector<uint32_t> findWordMatches(const std::string w, const std::vector<std::string>& words, const std::vector<std::string>& sortedWords)
{
	std::vector<uint32_t> matches;
	auto wT = w;

	std::sort(wT.begin(), wT.end());

	auto f = std::find(sortedWords.begin(), sortedWords.end(), wT);

	while (f != sortedWords.end())
	{
		if (words[f - sortedWords.begin()] != w)
			matches.push_back(f - sortedWords.begin());

		f = std::find(f+1, sortedWords.end(), wT);
	}

	return matches;
}

void replaceChar(std::string& s, const std::string w, const char a, const char b)
{
	for (auto i = 0; i<s.size(); i++)
	{
		if (s[i] == a) s[i] = b;
		else if (w[i] == b) s[i] = '?';
	}
}

std::vector<uint32_t> findSquareMatches(std::string w, const std::vector<uint64_t>& sqIdx, const std::vector<uint64_t>& squares)
{
	uint32_t startIdx = sqIdx[w.size()-1];
	uint32_t endIdx = sqIdx[w.size()]-1;
	std::stringstream ss;
	std::vector<uint32_t> matches;

	for(auto i = startIdx; i <= endIdx; i++)
	{
		ss << squares[i];
		auto s = ss.str();

		for (auto j = 0; j <s.size(); j++)
		{
			if (s[j] >= '0' && s[j] <= '9')
				replaceChar(s, w, s[j], w[j]);
		}

		if (s == w)
			matches.push_back(i);

		ss.str(std::string());
	}

	return matches;
}

void computeSquares(std::vector<uint64_t>& squares, std::vector<uint64_t>& sqIdx)
{
	uint64_t i = 1;
	uint64_t i2 = i*i;
	uint64_t si = 10;

	sqIdx.push_back(0);

	while (i2 < MAX_SQUARE)
	{
		squares.push_back(i2);

		if (i2 > si)
		{
			sqIdx.push_back(squares.size()-1);
			si *= 10;
		}

		i++;
		i2 = i*i;
	}

	sqIdx.push_back(squares.size());

}

std::vector<std::pair<uint64_t, uint64_t>> findMatchingPairs(std::vector<uint32_t> sq1, std::vector<uint32_t> sq2, std::string w1, std::string w2, std::vector<uint64_t>& squares)
{
	std::vector<std::pair<uint64_t, uint64_t>> matches;
	std::stringstream ss1, ss2;
	std::string st1, st2;
	std::vector<char> c1, c2;

	
	for (auto s1: sq1)
	{
		ss1 << squares[s1];
		st1 = ss1.str();
		
		c1.clear();
		c1.insert(c1.begin(), '?', 10);

		for (auto i = 0;i<w1.size();i++)
		{
			c1[st1[i]-'0'] = w1[i];
		}


		for (auto s2: sq2)
		{
			if (s1 == s2) continue;

			ss2 << squares[s2];
			st2 = ss2.str();
			
			c2.clear();
			c2.insert(c2.begin(), '?', 10);

			for (auto i = 0;i<w2.size();i++)
			{
				c2[st2[i]- '0'] = w2[i];				
			}

			if (std::equal(c1.begin(), c1.end(), c2.begin()))
			{
				matches.push_back(std::make_pair(squares[s1], squares[s2]));
			}

			ss2.str(std::string());
		}

		ss1.str(std::string());		
	}

	return matches;
}

int main(int argc, char** argv)
{
	std::vector<std::string> words;
	std::vector<std::string> sortedWords;

	std::vector<uint64_t> squares;
	std::vector<uint64_t> sqIdx;
	
	std::vector<uint64_t> results;

	readFile(words);
	sortWords(words,sortedWords);
	computeSquares(squares, sqIdx);

	for (auto w: words)
	{
		auto r = findWordMatches(w, words, sortedWords);

		if (r.size() > 0)
		{
			auto sq1 = findSquareMatches(w, sqIdx, squares);

			if (sq1.size() > 0)
			{
				for (auto m: r)
				{
					auto sq2 = findSquareMatches(words[m], sqIdx, squares);
					auto p = findMatchingPairs(sq1, sq2, w, words[m], squares);

					for (auto x: p)
					{
						results.push_back(x.first);
						results.push_back(x.second);
						
						//std::cout << w << ":" << x.first << " -- " << words[m] << ":" << x.second << std::endl;						
					}

				}
			}

		}
	}

	std::cout << *std::max_element(results.begin(), results.end()) << std::endl;

	return 0;

}