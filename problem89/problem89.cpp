//Author: Bruce Hart <bruce.hart@gmail.com>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define FILE_PATH   "p089_roman.txt"

std::string encode_roman(uint32_t x)
{
    std::vector<std::string> numerals = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    std::vector<uint32_t> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    std::string r;

    for(int i=0;i<values.size();i++)
    {
        while (x >= values[i])
        {
            r += numerals[i];
            x -= values[i];
        }
    }

    return r;
}

uint32_t decode_roman(std::string r)
{
    std::vector<std::string> numerals = {"CM", "M", "CD", "D", "XC", "C", "XL", "L", "IX", "X", "IV", "V", "I"};
    std::vector<uint32_t> values = {900, 1000, 400, 500, 90, 100, 40, 50, 9, 10, 4, 5, 1};

    uint32_t result = 0;
    
    for (int i=0;i<numerals.size();i++)
    {
        auto p = r.find(numerals[i]);

        while (p != std::string::npos)
        {
            result += values[i];
            r.erase(p, numerals[i].length());
            p = r.find(numerals[i]);
        }
    }

    return result;
}

int main(int argc, char** argv)
{   
    std::ifstream f(FILE_PATH);

    std::string numeral;
    uint32_t val;
    std::string min;
    uint32_t saved = 0;

    while(f>>numeral)
    {
        val = decode_roman(numeral);
        min = encode_roman(val);

        saved += (numeral.length() - min.length());
        //std::cout << numeral << " (" << val << ") --> " << min << " (" << saved << ")" << std::endl;
    }

    std::cout << saved << std::endl;

    return 0;
}