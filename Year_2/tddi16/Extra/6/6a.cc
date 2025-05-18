#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <chrono>

struct Node
{
    int value;
    bool visited{false};
    std::vector<int> edges;
};

using Graph = std::vector<Node>;

//----------BFS----------//
void bfs(Graph& graph, int node)
{
    auto it = std::find_if(graph.begin(), graph.end(), [node](const Node& n) {
        return n.value == node;
    });

    if (it == graph.end())
        return;

    std::queue<int> q;
    q.push(it - graph.begin());

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
//----------INSERT----------//


    
    int n;
    std::vector<std::set<int>> inaNodesVec;

    while (std::cin >> n && n != 0)
    {    

        Graph graph(n+1);

        int startVertex;
        while (std::cin >> startVertex && startVertex != 0)
        {
            Node node;
            std::cin >> node.value;

            int edge;
            while (std::cin >> edge && edge != 0)
                node.edges.push_back(edge);

            graph.push_back(node);
        }
    


//----------TESTS----------//

    int numberOfTests;
    

    while (std::cin >> numberOfTests && numberOfTests != 0)
    {
        for (int i{}; i < numberOfTests; i++)
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
}
   // for (auto &n : inaNodesVec)
   //     n.erase(n.begin());

    for (auto const& n : inaNodesVec)
    {
        std::cout << n.size();
        for (int node: n)
            std::cout << " " << node;
        std::cout << std:: endl;
    }
    
}