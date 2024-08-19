#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

// Function to find the shortest addition chain using dynamic programming with caching
int min_multiplications(int k, std::unordered_map<int, int>& cache) {
    if (cache.find(k) != cache.end()) {
        return cache[k];
    }

    std::vector<int> chain = {1};
    std::queue<std::vector<int>> q;
    q.push(chain);

    while (!q.empty()) {
        std::vector<int> current_chain = q.front();
        q.pop();

        int last = current_chain.back();

        if (last == k) {
            cache[k] = current_chain.size() - 1;
            return cache[k]; // Number of multiplications is size-1
        }

        for (int i = current_chain.size() - 1; i >= 0; --i) {
            int next = last + current_chain[i];
            if (next <= k) {
                std::vector<int> new_chain = current_chain;
                new_chain.push_back(next);
                q.push(new_chain);
            }
        }
    }

    return 0; // Should not reach here for k >= 1
}

int main() {
    std::unordered_map<int, int> cache; // Cache to store computed m(k) values
    int sum = 0;

    for (int k = 1; k <= 200; ++k) {
        int min_mults = min_multiplications(k, cache);
        sum += min_mults;
        //std::cout << "m(" << k << ") = " << min_mults << "\n";
    }

    std::cout << sum << std::endl;

    return 0;
}
