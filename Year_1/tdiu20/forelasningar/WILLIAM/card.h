#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
public:

    Card(std::string const& in_suit, int const in_value);

    std::string to_string() const;
    int get_value() const;

private:
    int     value;
    std::string  suit;
};


#endif