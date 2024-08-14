#include <iostream>
#include <vector>
#include <unordered_map>

constexpr int TRIANGLE_SIZE = 64;

// Persistent cache for storing neighbors of each index
std::unordered_map<int, std::vector<int>> neighborsCache;

// Function to create an empty triangle of size TRIANGLE_SIZE
std::vector<char> createEmptyTriangle()
{
    return std::vector<char>(TRIANGLE_SIZE, 'x');
}

// Function to get the neighbors of a cell at the given index
std::vector<int> getNeighbors(int index)
{
    // Check if the neighbors for this index are already cached
    if (neighborsCache.find(index) != neighborsCache.end())
    {
        return neighborsCache[index];
    }

    std::vector<int> neighbors;
    std::unordered_map<int, int> totalRows = {{1,0}, {4,1}, {9,2}, {16,3}, {25,4}, {36,5}, {49,6}, {64,7}};

    // Calculate row and column based on index
    int row = 0, rowSize = 1, i = index;
    while (i >= rowSize)
    {
        i -= rowSize;
        row++;
        rowSize += 2;
    }
    int col = i;

    // Add neighbors based on row and column position
    if (col % 2 == 1)
    {
        if (row > 0)
            neighbors.push_back(index - rowSize + 2);
    }
    else
    {        
        if (row < totalRows[TRIANGLE_SIZE])
            neighbors.push_back(index + rowSize + 1);
    }

    if (col > 0)
        neighbors.push_back(index - 1);

    if (col < rowSize - 1)
        neighbors.push_back(index + 1);

    // Cache the computed neighbors
    neighborsCache[index] = neighbors;

    return neighbors;
}

// Function to check if a color can be placed at a given cell without conflicting with neighbors
bool isValidColoring(const std::vector<char>& tri, int cell, char color)
{
    for (int neighbor : getNeighbors(cell))
    {
        if (tri[neighbor] == color)
            return false;
    }
    return true;
}

// Recursive function to count the number of valid colorings
long long countColorings(std::vector<char>& tri, int idxStart = 0)
{
    long long count = 0;
    static const std::vector<char> colors = {'r', 'g', 'b'};

    int emptyCell = -1;
    for (int i = idxStart; i < TRIANGLE_SIZE; ++i)
    {
        if (tri[i] == 'x')
        {
            emptyCell = i;
            break;
        }
    }

    if (emptyCell == -1)
        return 1; // All cells are filled

    for (char color : colors)
    {
        if (isValidColoring(tri, emptyCell, color))
        {
            tri[emptyCell] = color;
            count += countColorings(tri, emptyCell + 1);
            tri[emptyCell] = 'x'; // Backtrack
        }
    }

    return count;
}

int main()
{
    std::vector<char> triangle = createEmptyTriangle();
    std::cout << countColorings(triangle) << std::endl;
    return 0;
}
