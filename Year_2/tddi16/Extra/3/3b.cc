#include <iostream>
#include <vector>
#include <cmath>

struct Node {
    int marbles;
    std::vector<int> children;
};

int dfs(int node, std::vector<Node>& tree, int& moves) {
    int balance = tree[node].marbles - 1;

    for (int child : tree[node].children) {
        balance += dfs(child, tree, moves);
    }

    moves += abs(balance);
    return balance;
}

int main() {
    std::vector<int> result;
    while (true) {
        int n;
        std::cin >> n;
        if (n == 0) break;

        std::vector<Node> tree(n + 1);

        for (int i = 0; i < n; ++i) {
            int v, marbles, d;
            std::cin >> v >> marbles >> d;
            tree[v].marbles = marbles;
            for (int j = 0; j < d; ++j) {
                int child;
                std::cin >> child;
                tree[v].children.push_back(child);
            }
        }

        int moves = 0;
        dfs(1, tree, moves);
        result.push_back(moves);
    }
    for (const auto &moves : result)
        std::cout << moves << std::endl;
    return 0;
}
