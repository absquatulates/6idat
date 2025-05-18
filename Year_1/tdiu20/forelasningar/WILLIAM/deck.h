#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <vector>

class Deck
{
    public:

    Deck();

    void shuffle();
    bool is_empty() const;
    Card draw();

private:

    std::vector<Card> cards;
};

#endif