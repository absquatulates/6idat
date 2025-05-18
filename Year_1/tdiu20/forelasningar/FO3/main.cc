#include "deck.h"
#include "card.h"
#include <iostream>

using namespace std;

int main()
{
    Deck deck1{};
    deck1.shuffle();
    while (! deck1.is_empty() )
    {

        deck1[1];

        Card card1{ deck1.draw() };
        std::cout << card1.to_string() << std::endl;
    }
    

}