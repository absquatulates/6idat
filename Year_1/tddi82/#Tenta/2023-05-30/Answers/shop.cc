#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

//Givna produkter, ska initiseras i behÃ¥llaren sÃ¥hÃ¤r:

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


std::map<std::string, std::vector<std::string>> read(std::string const& file)
{
    std::map<std::string, std::vector<std::string>> ret{};
    std::ifstream ifs{file};
    std::string line{};
    
    while(std::getline(ifs, line))
    {
        std::istringstream iss{line};
        std::string name{};
        iss >> name;

        std::vector<std::string> products{};
        std::string product{};
        while (iss >> product)
        {products.push_back(product);}
        ret[name] = products;
    }
    return ret;
}

int main()
{

    auto customers{read("customers.txt")};

    std::string name{};

    std::cout << "Enter name (ctrl+D to exit): ";
    while (std::cin >> name)
    {
        auto it{customers.find(name)};
        if (it == customers.end())
        {std::cout << "This person isn't shopping!" << std::endl;}
        else 
        {
            int tot{};
            std::cout << "Your cart contains: " << std::endl;
            for (auto const& product : it->second)
            {
                std::cout << product << std::endl;
                tot += products.at(product);
            }
            std::cout << "Your total is: " << tot << std::endl;
        }
        std::cout << "Enter name (ctrl+D to exit): ";       
    }
    return 0;
}
