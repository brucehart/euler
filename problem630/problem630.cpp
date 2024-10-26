#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <tuple>
#include <numeric>

// Structure to hold 2D points
struct Point {
    int x, y;
};

// Function to calculate line parameters (slope and intercept) from two points
// Returns normalized coefficients of the line equation: ay + bx + c = 0
std::tuple<long long, long long, long long> calculateLineEquation(Point p1, Point p2) {
    long long deltaY = p1.y - p2.y;
    long long deltaX = p2.x - p1.x;
    long long intersect = -(p2.x * p1.y - p1.x * p2.y);
    
    // Find GCD to normalize coefficients
    long long commonDivisor = std::gcd(std::abs(deltaY), std::abs(deltaX));
    
    // Normalize the line equation to ensure unique representation
    if (deltaX < 0 || (deltaX == 0 && deltaY < 0)) {
        deltaY *= -1;
        deltaX *= -1;
        intersect *= -1;
    }
    
    return std::make_tuple(
        deltaY / commonDivisor,
        deltaX / commonDivisor,
        intersect / commonDivisor
    );
}

// Generate points using the given sequence formula
std::vector<Point> generatePoints(int numPoints) {
    long long currentNum = 290797;
    std::vector<Point> points;
    
    // Generate 2*numPoints numbers for x and y coordinates
    for (int i = 0; i < numPoints; i++) {
        // Generate x coordinate
        currentNum = (currentNum * currentNum) % 50515093;
        int x = (currentNum % 2000) - 1000;
        
        // Generate y coordinate
        currentNum = (currentNum * currentNum) % 50515093;
        int y = (currentNum % 2000) - 1000;
        
        points.push_back({x, y});
    }
    
    return points;
}

// Calculate the number of unique lines and pairs of parallel lines
std::pair<int, long long> calculateLineStatistics(int numPoints) {
    // Generate points using the sequence
    std::vector<Point> points = generatePoints(numPoints);
    
    // Set to store unique lines
    std::set<std::tuple<long long, long long, long long>> uniqueLines;
    
    // Generate all possible lines through pairs of points
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            uniqueLines.insert(calculateLineEquation(points[i], points[j]));
        }
    }
    
    // Map to count lines with same slope
    std::map<std::pair<long long, long long>, int> slopeCount;
    
    // Count lines with same slope (parallel lines)
    for (const auto& line : uniqueLines) {
        slopeCount[{std::get<0>(line), std::get<1>(line)}]++;
    }
    
    // Calculate total number of parallel line pairs
    long long parallelPairs = 0;
    int totalLines = uniqueLines.size();
    
    for (const auto& [slope, count] : slopeCount) {
        // For each slope, calculate number of parallel line pairs
        parallelPairs += (long long)count * (totalLines - count);
    }
    
    return {totalLines, parallelPairs};
}

int main() {
    auto [uniqueLines, parallelPairs] = calculateLineStatistics(2500);
    std::cout << parallelPairs << std::endl;
    return 0;
}