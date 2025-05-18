#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int moves;

int dfs(int v, const vector<int>& marbles, const vector<vector<int>>& children) {
    int excess = marbles[v] - 1;
    for (int child : children[v]) {
        excess += dfs(child, marbles, children);
    }
    moves += abs(excess);
    return excess;
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
        dfs(1, marbles, children);
        result.push_back(moves);
        
    }
    for (const auto &moves : result)
        cout << moves << endl;

    return 0;
}
