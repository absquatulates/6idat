#ifndef STATES_H
#define STATES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int const MENU_STATE{};
int const GAME_STATE{1};
int const GAME_OVER_STATE{2};
int const GAME_WON_STATE{3};

class State
{
public:
    virtual ~State() = default;
    virtual void update() = 0;
    virtual void handle(sf::Event event) = 0;
    virtual void render(sf::RenderTarget & target) = 0;
    virtual int get_next_state() = 0;
protected:

    /* Background */
    sf::Texture background_texture{};
    sf::Sprite background{};
};


#endif //STATE_H