#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string line{};
    std::vector<std::string> vec{};
    bool flag;
    std::string output{};

    while(std::getline(std::cin, line))
        vec.push_back(line);

    for (std::string& row : vec)
    {
        for (char& letter : row)
        {
            if (letter == '"')
            {
                if (!flag)
                {
                    std::cout << "``";
                    flag = true;
                }
                else
                {
                    std::cout << "''";
                    flag = false;
                }
            }
            else
                std::cout << letter;
        }
        std::cout << std::endl;
    }
}
