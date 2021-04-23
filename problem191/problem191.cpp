//Author: Bruce Hart <bruce.hart@gmail.com>

#include <iostream>
#include <map>

#define NUM_DAYS    30
#define MAX_ABSENT  3
#define MAX_LATE    2

std::map<int,uint64_t> matched;

uint64_t count_matches(int days, int absent, int late)
{
    uint64_t count;
    
    if (absent >= 3)
       return 0;

    if (late >= 2)
        return 0;

    if (days == 0)
        return 1;

    int idx = days*MAX_ABSENT*MAX_LATE + absent*MAX_LATE + late;

    if (matched.count(idx) > 0)
        return matched[idx];

    count = count_matches(days-1, 0, late);
    count += count_matches(days-1, absent+1, late);
    count += count_matches(days-1, 0, late+1);

    matched[idx] = count;
    return count;
}

int main(int argc, char** argv)
{
    std::cout << count_matches(NUM_DAYS, 0, 0) << std::endl;
}