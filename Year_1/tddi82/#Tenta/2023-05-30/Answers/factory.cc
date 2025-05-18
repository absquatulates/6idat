#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>

struct Product
{
    std::string name;
    double weight;
    double volume;
};

std::ostream& operator<<(std::ostream& os, Product product)
{
    os << product.name << " [" << product.weight << " kg, " << product.volume << " m^3]";
    return os;
}

std::istream& operator>>(std::istream& is, Product& product)
{
    is >> product.name >> product.weight >> product.volume;
    return is;
}

double density(Product product)
{
    return product.weight / product.volume;
}

std::vector<Product> read()
{
    std::vector<Product> p;
    std::ifstream file{"factory.txt"};
    if (file.is_open())
    {
        std::copy(std::istream_iterator<Product>(file),
             std::istream_iterator<Product>(), 
             std::inserter(p, p.end()));
        file.close();
    }
    else
    {std::cout << "filen öppnades inte" << std::endl;}
    return p;
}

int main()
{
    // Implementera uppgiften hÃ¤r
    std::vector<Product> products = read();
    int lowDensTol{};
    int highDensTol{};
    int thresh;

    std::cout << "Enter the lower density tolerance: ";
    std::cin >> lowDensTol;
    std::cout << "Enter the higher density tolerance: ";
    std::cin >> highDensTol;
    std::cout << "Enter the sequential fault threshold: ";
    std::cin >> thresh;

    auto it = std::search_n(products.begin(), products.end(), thresh, highDensTol,
                            [&lowDensTol](Product const& p, int highDensTol)
                            {
                                double curr_dens {density(p)};
                                return !(lowDensTol < curr_dens && curr_dens < highDensTol);
                            });

    if (it != products.end())
    {
        std::cout << "Found a faulty sequence after " << std::distance(products.begin(), it) <<"products: ";
        std::copy_n(it, thresh, std::ostream_iterator<Product>{std::cout, " "});
    }
}
