#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void topologicalSort(int n, vector<pair<int, int>>& edges) {
    // Adjacency list and in-degree array
    vector<vector<int>> adjList(n + 1);
    vector<int> inDegree(n + 1, 0);

    // Build the graph from the edges
    for (auto& edge : edges) {
        int u = edge.first, v = edge.second;
        adjList[u].push_back(v);
        inDegree[v]++;
    }

    // Queue for nodes with in-degree 0
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topOrder;

    // Process each node with in-degree 0
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topOrder.push_back(node);

        // Reduce the in-degree of adjacent nodes
        for (int neighbor : adjList[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Output the topological order
    for (int i = 0; i < topOrder.size(); i++) {
        cout << topOrder[i];
        if (i < topOrder.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    while (true) {
        int n, m;
        cin >> n >> m;

        if (n == 0 && m == 0) break; // Termination condition

        vector<pair<int, int>> edges;

        // Input edges (dependencies between tasks)
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }

        topologicalSort(n, edges);
    }

    return 0;
}
