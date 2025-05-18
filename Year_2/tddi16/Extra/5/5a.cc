#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_set>

int main()
{
    std::string word;
    std::vector<std::string> wordVector;
    std::unordered_set<std::string> compare{};
    std::vector<std::string> output;

    while (std::cin >> word)
    {
        wordVector.push_back(word);
        compare.insert(word);
    }

    for (auto const& word : wordVector)
    {
        for (int i = 1; i < word.length(); i++)
        {
            std::string firstPart{word.substr(0, i)};
            std::string secondPart{word.substr(i)};

            if (compare.find(firstPart) != compare.end() && compare.find(secondPart) != compare.end())
            {
                output.push_back(word);
                break;
            }
        }
    }

    for (auto const& word : output)
        std::cout << word << std::endl;
}