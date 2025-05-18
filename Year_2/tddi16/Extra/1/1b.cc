#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

bool sub(std::string const& s, std::string const& t)
{
    int i{};
    int j{};

    while (i < s.size() && j < t.size())
    {
        if (s.at(i) == t.at(j))
            i++;

        j++;
    }

    return i == s.size();
}

int main()
{
    std::string s{};
    std::string t{};
    std::pair<std::string, std::string> p{};
    std::vector<std::pair<std::string, std::string>> vec{};

    while (std::cin >> s >> t)
    {
        p = std::make_pair(s, t);
        vec.push_back(p);
    }

    for (std::pair<std::string, std::string> pa : vec)
    {
        if (sub(pa.first, pa.second))
        std::cout << "Yes" << std::endl;
        else
        std::cout << "No" << std::endl;
    }   
}