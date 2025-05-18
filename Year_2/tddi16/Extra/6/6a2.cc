#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

void bfs(const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int start) {
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

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
    std::set<int> inaccessibleNodes;
    std::vector<std::set<int>> listOfInaccessibleNodes; 
    while (std::cin >> n && n != 0) 
    {
        inaccessibleNodes.clear();
        std::vector<std::vector<int>> graph(n + 1);

        int startNode;
        while (std::cin >> startNode && startNode != 0) {
            int endNode;
            while (std::cin >> endNode && endNode != 0) {
                graph[startNode].push_back(endNode);
            }
        }

        int numberOfTests;
        std::cin >> numberOfTests;


        for (int i = 0; i < numberOfTests; i++) {
            int testNode;
            std::cin >> testNode;

            std::vector<bool> visited(n + 1, false);
            bfs(graph, visited, testNode);

                          
            for (int j = 1; j <= n; j++) 
            {
                if (!visited[j])
                    inaccessibleNodes.insert(j);
            }

            listOfInaccessibleNodes.push_back(inaccessibleNodes);
        }
        
    }
        for (auto const& n : listOfInaccessibleNodes)
        {
            std::cout << n.size();
            for (auto const& node : n)
                std::cout << " " << node;
            std::cout << std::endl;
        }
    

    return 0;
}
