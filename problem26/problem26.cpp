#include <iostream>
#include <vector>

int findCycleLength(int d) {
    std::vector<int> remainders(d, 0);
    int value = 1;
    int position = 0;

    while (remainders[value] == 0 && value != 0) {
        remainders[value] = position;
        value *= 10;
        value %= d;
        position++;
    }

    if (value != 0) {
        return position - remainders[value];
    } else {
        return 0;
    }
}

int main() {
    int maxCycleLength = 0;
    int denominatorWithMaxCycle = 0;

    for (int d = 2; d < 1000; d++) {
        int cycleLength = findCycleLength(d);
        if (cycleLength > maxCycleLength) {
            maxCycleLength = cycleLength;
            denominatorWithMaxCycle = d;
        }
    }

    std::cout <<  denominatorWithMaxCycle << std::endl;  

    return 0;
}

