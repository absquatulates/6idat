#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int moves;

int dfs(int v, const vector<int>& marbles, const vector<vector<int>>& children) {
    int excess = marbles[v] - 1; // Calculate the excess marbles at the current vertex
    for (int child : children[v]) {
        excess += dfs(child, marbles, children); // Traverse the children and calculate their excess
    }
    moves += abs(excess); // Add the absolute value of excess to the total moves
    return excess; // Return the excess to parent calls
}

int main() {
    vector<int> result;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        vector<int> marbles(n + 1);
        vector<vector<int>> children(n + 1);

        for (int i = 0; i < n; ++i) {
            int v, m, d;
            cin >> v >> m >> d;
            marbles[v] = m;
            children[v].resize(d);
            for (int j = 0; j < d; ++j) {
                cin >> children[v][j];
            }
        }

        moves = 0;
        dfs(1, marbles, children); // Start DFS from the root node
        result.push_back(moves);
        
    }
    for (const auto &moves : result)
        cout << moves << endl;
    return 0;
}
