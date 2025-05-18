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

bool Card::operator<(Card const& rhs) const
{
    return value < rhs.value;
}

bool Card::operator>(Card const& rhs) const
{
    return rhs < *this;
}

std::ostream& operator<<(std::ostream& os, Card const& rhs)
{
    os << rhs.to_string();
    return os;
}

Card& Card::operator++()
{
    value++;
    return *this;
}

Card Card::operator++(int)
{
    Card tmp {*this};
    ++(*this);
    return tmp;
}