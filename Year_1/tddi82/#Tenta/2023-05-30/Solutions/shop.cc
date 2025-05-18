#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

std::map<std::string, std::vector<std::string>> read_customers(std::string const& filename)
{
    std::map<std::string, std::vector<std::string>> result { };
    
    std::ifstream ifs { filename };

    std::string line;
    while (std::getline(ifs, line))
    {
        std::istringstream iss { line };
        std::string name;
        iss >> name;

        std::vector<std::string> products { };
        std::string product;
        while (iss >> product)
        {
            products.push_back(product);
        }

        result[name] = products;
    }

    return result;
}

std::map<std::string, int> const products {
    { "Apples", 20 },
    { "Bananas", 15 },
    { "Oranges", 25 },
    { "Grapes", 30 },
    { "Strawberries", 30 },
    { "Watermelon", 10 },
    { "Pineapple", 35 },
    { "Kiwi", 5 },
    { "Blueberries", 25 },
    { "Mango", 40 }    
};

int main()
{
    auto customers { read_customers("customers.txt") };

    std::string name;

    std::cout << "Enter name (ctrl+D to exit): ";
    while (std::cin >> name)
    {
        auto it = customers.find(name);
        if (it == customers.end())
        {
            std::cout << "This person isn't shopping!" << std::endl;
        }
        else
        {
            std::cout << "Your cart contains: " << std::endl;

            int total { };
            for (auto const& product : it->second)
            {
                std::cout << product << std::endl;
                total += products.at(product);
            }
            std::cout << "Your total is: " << total << std::endl;
        }
        std::cout << "Enter name (ctrl+D to exit): ";
    }
}
