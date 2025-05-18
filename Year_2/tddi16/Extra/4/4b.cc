#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int t;
    std::cin >> t;

    std::vector<std::vector<int>> allResults;

    while (t--) {
        int n;
        int m;
        std::cin >> n >> m;

        std::vector<int> stack(n);
        for (int i = 0; i < n; ++i) {
            stack[i] = i + 1;
        }

        std::unordered_map<int, int> position;
        for (int i = 0; i < n; ++i) {
            position[stack[i]] = i;
        }

        std::vector<int> results;

        for (int i = 0; i < m; ++i) {
            int movieId;
            std::cin >> movieId;

            int pos = position[movieId];
            results.push_back(pos);

            for (int j = pos; j > 0; --j) {
                stack[j] = stack[j - 1];
                position[stack[j]] = j;
            }
            stack[0] = movieId;
            position[movieId] = 0; 
        }

        allResults.push_back(results);
    }

    for (const auto& results : allResults) {
        for (int result : results) {
            std::cout << result << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
