#include <iostream>
#include <vector>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

static const cpp_int MOD = 1000000007; 
std::vector<std::map<int, cpp_int>> sum_sets;
std::vector<std::map<int, cpp_int>> count_sets;
std::vector<int> initial_set;

int leadingOnes(int n) {
    int bit = (1 << 9);
    int count = 0;

    while ((n & bit) > 0)
    {
        count++;
        bit >>= 1;
    }

    return count;
}

int trailingOnes(int n) {
    int bit = 1;
    int count = 0;

    while ((n & bit) > 0)
    {
        count++;
        bit <<= 1;
    }

    return count;
}

bool containsThreeConsecutiveOnes(int n) {  
    do{
        if ((n & 7) == 7)
            return true;                            
    } while (n >>= 1);

    return false;
}

void buildInitialSet(){
    for (int i = 0; i < (1 << 11); i++) {
        if (!containsThreeConsecutiveOnes(i)) {
            initial_set.push_back(i);
        }
    }
}

void buildSet0(){  
    sum_sets.push_back(std::map<int, cpp_int>());
    count_sets.push_back(std::map<int, cpp_int>());

    for (int x: initial_set) {
        if (x & 1 == 1)
        {
            sum_sets[0][x] = (x*x) % MOD;
            count_sets[0][x] = 1;
        }
    }
}

void buildSet5()
{
    cpp_int scaleFactor = (1ULL << 50) % MOD;
    cpp_int sq_sum = 0;
    cpp_int count = 0;
    sum_sets.push_back(std::map<int, cpp_int>());
    count_sets.push_back(std::map<int, cpp_int>());

    for (int x = 0; x <= 7; x++)
    {
        count = 0;
        int trailing = trailingOnes(x);        

        for (const auto& [y, ySum] : sum_sets[4])
        {
            if (leadingOnes(y) + trailing >= 3 || y == 0)
                continue;
            
            count += count_sets[4][y];
            sq_sum += ySum; 
        }

        sq_sum += (((x*x) % MOD) * scaleFactor * count) % MOD;
        sq_sum %= MOD;
        sum_sets[5][x] = sq_sum;
        count_sets[5][x] = count;
    }
}
    

void buildSetN(int n)
{    
    cpp_int scaleFactor = (1ULL << (10*n)) % MOD;
    cpp_int sq_sum = 0;
    cpp_int count = 0;
    sum_sets.push_back(std::map<int, cpp_int>());
    count_sets.push_back(std::map<int, cpp_int>());

    for (int x: initial_set)
    {
        count = 0;
        int trailing = trailingOnes(x);        

        for (const auto& [y, ySum] : sum_sets[n-1])
        {
            if (leadingOnes(y) + trailing >= 3)
                continue;

            count += count_sets[n-1][y];            
            sq_sum += ySum; 
        }

        sq_sum += (((x*x) % MOD) * scaleFactor * count) % MOD;
        sq_sum %= MOD;
        sum_sets[n][x] = sq_sum;
        count_sets[n][x] = count;
    }
}

cpp_int computeLastSum()
{
    cpp_int sum = 0;
    cpp_int count = 0;
    
    for (const auto& [x, xSum] : sum_sets[4])
    {
        if (x >= 0b1110000110) break;
        count += count_sets[5][x];
        sum += xSum;
    }

    for(const auto& [x, xSum] : sum_sets[3])
    {
        if (x >= 0b1111001001) break;
        count += count_sets[4][x];
        sum += xSum;
    }

    for(const auto& [x, xSum] : sum_sets[2])
    {
        if (x >= 0b1011111100) break;
        count += count_sets[3][x];
        sum += xSum;
    }

    for(const auto& [x, xSum] : sum_sets[1])
    {
        if (x >= 0b0001000000) break;
        count += count_sets[2][x];
        sum += xSum;
    }

    sum += ((1ULL << 54) * count) % MOD;
    return sum;
}

int main() {
    cpp_int totalSum = 0;

    buildInitialSet();
    buildSet0();

    for (int i = 1;i<=4;i++)
        buildSetN(i);
    
    buildSet5();

    for (int i = 0; i <= 5; i++)
    {
        for (const auto& [x, xSum] : sum_sets[i])
        {
            totalSum += xSum;
        }
    }

    totalSum += computeLastSum();
    totalSum %= MOD;

    std::cout << totalSum << std::endl;
   
    return 0;
}