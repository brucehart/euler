#include <iostream>


int main() {
    const int limit = 1000000; 
    int count = 0;
    

    for (int innerSide = 1;; ++innerSide) {
       int squareSize = innerSide;
       int tiles = 0;
       int prevCount = count;

       while (tiles <= limit)
       {
          squareSize += 2;  
          tiles = squareSize * squareSize - innerSide * innerSide;
          if (tiles > limit) break;
          count++;
       }       

       if (count == prevCount) break;
    }

    std::cout << count << std::endl;

    return 0;
}
