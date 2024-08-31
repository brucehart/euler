#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <sstream>

int V;  // Number of vertices in the graph

int minKey(std::vector<int>& key, std::vector<bool>& mstSet) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

int primMST(std::vector<std::vector<int>>& graph) {
    std::vector<int> parent(V);  // Array to store constructed MST
    std::vector<int> key(V, INT_MAX);  // Key values used to pick minimum weight edge in cut
    std::vector<bool> mstSet(V, false);  // To represent set of vertices included in MST
    int totalWeightMST = 0;
    int totalWeight = 0;

    key[0] = 0;      // Make key 0 so that this vertex is picked as the first vertex
    parent[0] = -1;  // First node is always the root of MST

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Calculate the total weight of the MST
    for (int i = 1; i < V; i++) {
        totalWeightMST += graph[i][parent[i]];
    }

    // Calculate the total weight of the original graph
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != INT_MAX) {
                totalWeight += graph[i][j];
            }
        }
    }
    
    return totalWeight - totalWeightMST;
}

int main() {
    std::ifstream file("0107_network.txt");

    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        return 1; // exit if file not found
    }

    std::string line;
    std::vector<std::vector<int>> graph;

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        std::string entry;
        while (std::getline(ss, entry, ',')) {
            if (entry == "-") {
                row.push_back(INT_MAX);
            } else {
                row.push_back(std::stoi(entry));
            }
        }
        graph.push_back(row);
    }

    file.close();

    V = graph.size();

    int removedWeight = primMST(graph);
    std::cout << removedWeight << std::endl;

    return 0;
}

