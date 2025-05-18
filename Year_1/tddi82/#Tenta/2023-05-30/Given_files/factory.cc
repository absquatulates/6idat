#include <iostream>
#include <string>

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

int main()
{
    // Implementera uppgiften hÃ¤r
}
