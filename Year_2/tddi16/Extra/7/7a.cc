#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

std::vector<int> topologicalSort(int n, std::vector<std::pair<int, int>>& edges) 
{

    std::vector<std::vector<int>> adjList(n + 1);
    std::vector<int> inDegree(n + 1, 0);

    for (auto& edge : edges) 
    {
        int u = edge.first, v = edge.second;
        adjList[u].push_back(v);
        inDegree[v]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= n; i++) 
    {
        if (inDegree[i] == 0)
            q.push(i);
    }

    std::vector<int> topOrder;

    while (!q.empty()) 
    {
        int node = q.front();
        q.pop();
        topOrder.push_back(node);

        for (int neighbor : adjList[node]) 
        {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return topOrder;
}


int main()
{
    std::vector<int> topOrder{};
    while (true)
    {
        int n;
        int m;
        std::cin >> n >> m;

        if (n == 0 && m == 0)
            break;

        std::vector<std::pair<int, int>> edges;

        for (int k{}; k < m; ++k)
        {
            int i;
            int j;
            std::cin >> i >> j;
            edges.push_back({i, j});
        }
        topOrder = topologicalSort(n, edges);
    }

    for (int i = 0; i < topOrder.size(); i++) 
    {
        std::cout << topOrder[i];
        if (i < topOrder.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}