#include <iostream>
#include <vector>
#include <map>

std::map<int, std::vector<int>> gridRows;

int sumDigits(int n){
    int sum = 0;
    while (n > 0){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

bool validSet(int row1, int row2, int row3){
    int a = row1 % 10;
    int b = row2 % 10;
    int c = row3 % 10;
    int d = (row1 / 10) % 10;
    int e = (row2 / 10) % 10;
    int f = (row3 / 10) % 10;
    int g = (row1 / 100) % 10;
    int h = (row2 / 100) % 10;
    int i = (row3 / 100) % 10;
    int j = (row1 / 1000) % 10;
    int k = (row2 / 1000) % 10;
    int l = (row3 / 1000) % 10;

    int s = sumDigits(row1);
    int w = s - a - b - c;
    
    if (w < 0 || w > 9)
        return false;

    int x = s - d - e - f;
    if (x < 0 || x > 9)
        return false;

    int y = s - g - h - i;
    if (y < 0 || y > 9)
        return false;

    int z = s - j - k - l;
    if (z < 0 || z > 9)
        return false;
    
    if (w + x + y + z != s)
        return false;
    
    if (a + e + i + z != s)
        return false;
    
    if (j + h + f + w != s)
        return false;

    return true;
}

int countSolutions(int row1){
    int count = 0;
    int s = sumDigits(row1);
 
    for (auto row2: gridRows[sumDigits(row1)]){
        if (row2 % 10 + row1 % 10 > s)
            continue;
        if ((row2/10) % 10 + (row1/10) % 10 > s)
            continue;
        if ((row2/100) % 10 + (row1/100) % 10 > s)
            continue;
        if ((row2/1000) % 10 + (row1/1000) % 10 > s)
            continue;

        if ((row2/10) % 10 + row1 % 10 > s)
            continue;
        
        if ((row1/1000) % 10 + (row2/100) % 10 > s)
            continue;

        for (auto row3: gridRows[sumDigits(row1)]){
            
            if (row3 % 10 + row2 % 10 + row1 % 10 > s)
                continue;
            if ((row3/10) % 10 + (row2/10) % 10 + (row1/10) % 10 > s)
                continue;
            if ((row3/100) % 10 + (row2/100) % 10 + (row1/100) % 10 > s)
                continue;
            if ((row3/1000) % 10 + (row2/1000) % 10 + (row1/1000) % 10 > s)
                continue;

            if (validSet(row1, row2, row3))
                count++;
        }    
    }

    return count;
}

int main(){
    unsigned long long count = 0;

    for (int i=0; i<=9999;i++){
        if (gridRows.find(sumDigits(i)) == gridRows.end()){
            gridRows[sumDigits(i)] = std::vector<int>();
        }
        gridRows[sumDigits(i)].push_back(i);
    }

    for (auto it = gridRows.begin(); it != gridRows.end(); it++){        
        //std::cout << it->first << ":" << it->second.size() << std::endl;
        for (int i=0; i<it->second.size(); i++){        
            count += countSolutions(it->second[i]);
        }        
    }

    std::cout << count << std::endl;

    return 0;
}