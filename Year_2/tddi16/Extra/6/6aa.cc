#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

struct Node
{
    int value;
    bool visited{false};
    std::vector<int> edges;
};

using Graph = std::vector<Node>;

//----------BFS----------//
void bfs(Graph& graph, int startNode)
{
    auto it = std::find_if(graph.begin(), graph.end(), [startNode](const Node& n) {
        return n.value == startNode;
    });

    if (it == graph.end())
        return;

    std::queue<int> q;
    int startIndex = it - graph.begin();
    q.push(startIndex);
    graph[startIndex].visited = true;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int edge : graph[curr].edges)
        {
            auto neighborIt = std::find_if(graph.begin(), graph.end(), [edge](const Node& n) {
                return n.value == edge;
            });

            if (neighborIt != graph.end() && !neighborIt->visited)
            {
                neighborIt->visited = true;
                q.push(neighborIt - graph.begin());
            }
        }
    }
}

int main()
{
    int n;
    std::vector<std::set<int>> inaNodesVec;

    while (std::cin >> n && n != 0)
    {    
        Graph graph;

        int startVertex;
        while (std::cin >> startVertex && startVertex != 0)
        {
            Node node;
            node.value = startVertex;

            int edge;
            while (std::cin >> edge && edge != 0)
                node.edges.push_back(edge);

            graph.push_back(node);
        }
    
        // ----------TESTS----------//
        int numberOfTests;
        std::cin >> numberOfTests;

        while (numberOfTests--)
        {
            int node;
            std::cin >> node;

            for (auto& n: graph)
                n.visited = false;

            bfs(graph, node);

            std::set<int> inaccessibleNodes;
            for (const auto& n : graph)
            {
                if (!n.visited)
                    inaccessibleNodes.insert(n.value);
            }

            inaNodesVec.push_back(inaccessibleNodes);
        }
    }

    // Output result

    for (auto & inaccessibleNodes : inaNodesVec)
    {
        inaccessibleNodes.erase(inaccessibleNodes.begin());
        std::cout << inaccessibleNodes.size();
        for (int node : inaccessibleNodes)
            std::cout << " " << node;
        std::cout << std::endl;
    }
}
