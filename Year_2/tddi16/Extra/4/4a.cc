#include <iostream>
#include <queue>
#include <vector>

int cost(std::priority_queue<int, std::vector<int>, std::greater<int>> & q)
{
    int totCost{};

    while (q.size() > 1)
    {
        int first{};
        int second{};
        int cost{};

        first = q.top();
        q.pop();
        second = q.top();
        q.pop();

        cost = first + second;
        q.push(cost);

        totCost += cost;
    }
    
    return totCost;
}

int main()
{
    std::vector<int> output;

    while (true)
    {
        int n{};
        std::cin >> n;
        if (n == 0) break;

        std::priority_queue<int, std::vector<int>, std::greater<int>> q;

        for (int i{}; i < n; i++)
        {
            int number{};
            std::cin >> number;
            q.push(number);
        }

        output.push_back(cost(q));
    }
    
    for (auto const& cost : output)
        std::cout << cost << std::endl;
}