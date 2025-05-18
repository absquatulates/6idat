#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int t;
    std::cin >> t;

    std::vector<std::vector<int>> allResults;

    for (int tests = 0; tests < t; ++tests) {
        int n, m;
        std::cin >> n >> m;

        std::unordered_map<int, int> position; // Track current positions
        std::vector<int> results;

        // Initialize each movie to its initial position
        for (int i = 1; i <= n; ++i) {
            position[i] = i - 1;
        }

        // Process each movie request
        for (int i = 0; i < m; ++i) {
            int movieId;
            std::cin >> movieId;

            int currentPos = position[movieId];
            results.push_back(currentPos);

            // Move accessed movie to the front and update positions
            for (auto& [key, pos] : position) {
                if (pos < currentPos) {
                    pos++; // Push all previous movies back by one position
                }
            }
            position[movieId] = 0; // Move the requested movie to the front
        }

        allResults.push_back(results);
    }

    // Output results
    for (const auto& results : allResults) {
        for (int result : results) {
            std::cout << result << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
