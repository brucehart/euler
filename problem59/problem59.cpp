//Author: Bruce Hart <bruce.hart@gmail.com>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

#define FILE_NAME   "p059_cipher.txt"

std::string transform_msg(const std::string& msg, int* x)
{
    std::string out;
    int n = 0;

    for (auto c: msg)    
        out.push_back(c^x[n++%3]);                             
    
    return out;
}

int score_msg(std::string m)
{
    int score = 0;

    for(char c: m)
    {
        if ((c >= 'a' && c <= 'z') || c == ' ' || (c >= '0' && c <= '9') || c == '.' || (c >= 'A' && c <= 'Z') ||  c == '?' || c == ':' || c == '\'' || c == ',' || c == '(' || c== '(')
            score++;
    }

    return score;
}

int main(int argc, char** argv)
{
    std::ifstream f(FILE_NAME);
    std::string sData;
    f >> sData;
    f.close();

    std::string oriM;
    char mm = 0;

    for (auto cc: sData)
    {
        if (cc == ',')
        {
            oriM.push_back(mm);
            mm = 0;
        }
        else
        {
            mm *= 10;
            mm += (cc-'0');
        }
    }

    oriM.push_back(mm);

    int p[3];
    std::string m;
    int bSc = 0;
    int sc = 0;
    std::string bM;
    int b[3];

    for (p[0]='a';p[0]<='z';p[0]++)
    {
    for (p[1]='a';p[1]<='z';p[1]++)
    {
    for (p[2]='a';p[2]<='z';p[2]++)
    {        
        m = transform_msg(oriM, p);
        sc = score_msg(m);

        if (sc > bSc)
        {
            bM = m;
            bSc = sc;
        }
    }}}
    
    uint64_t sum; 
    for(char c: bM) sum+=(int)c;

    std::cout << sum << std::endl;

    return 0;
}