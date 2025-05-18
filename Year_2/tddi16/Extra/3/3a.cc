#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>


int main()
{
    int M;
    int N;

    std::cin >> M >> N;

    std::unordered_map<std::string, int> hayPointDict;

    for (int i{}; i < M; i++ )
    {
        std::string word;
        int salary{};

        std::cin >> word >> salary;
        hayPointDict[word] = salary;
    }

    std::vector<int> salaryVec;
    for (int i{}; i < N; i++)
    {
        int totSalary{};
        std::string line;
        std::string word;

        while (std::getline(std::cin, line) && line != ".")
        {
            std::stringstream ss(line);
            while (ss >> word)
            {
                if (hayPointDict.find(word) != hayPointDict.end())
                {
                    totSalary += hayPointDict[word];
                }
            }
        }
        salaryVec.push_back(totSalary);
    }

    for (auto const& salary : salaryVec)
        std::cout << salary << std::endl;

}