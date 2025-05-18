#include "card.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Card::Card(std::string const& in_suit, int const in_value)
    : value{in_value}, suit{in_suit}
{
    if (value <=  0 or value > 13)
    {
        throw std::out_of_range{"Måste vara inom 1 till 13"};
    }
}

std::string Card::to_string() const
{
    std::ostringstream oss {};
    oss << std::setw(10) << suit << " " << value;
    return oss.str();
}

int Card::get_value() const
{
    return value;
}