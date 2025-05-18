#include <iostream>
#include <vector>
#include <queue>
#include <set>

// Function to perform BFS and mark all reachable nodes from the given start node
void bfs(const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int start) {
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Explore all adjacent vertices
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n;

    while (std::cin >> n && n != 0) {
        // Initialize graph as adjacency list (1-based indexing)
        std::vector<std::vector<int>> graph(n + 1);

        // Read the edges for the graph
        int startNode;
        while (std::cin >> startNode && startNode != 0) {
            int endNode;
            while (std::cin >> endNode && endNode != 0) {
                graph[startNode].push_back(endNode);
            }
        }

        // Read the number of test queries
        int numberOfTests;
        std::cin >> numberOfTests;

        // Process each test query
        for (int i = 0; i < numberOfTests; i++) {
            int testNode;
            std::cin >> testNode;

            // Perform BFS from the testNode to find all reachable vertices
            std::vector<bool> visited(n + 1, false);
            bfs(graph, visited, testNode);

            // Collect all inaccessible vertices
            std::set<int> inaccessibleNodes;
            for (int j = 1; j <= n; j++) {
                if (!visited[j]) {
                    inaccessibleNodes.insert(j);
                }
            }

            // Output the result for this test query
            std::cout << inaccessibleNodes.size();
            for (int node : inaccessibleNodes) {
                std::cout << " " << node;
            }
            std::cout << std::endl;
        }
    }

    return 0;
}