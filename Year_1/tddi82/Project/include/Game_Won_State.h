#ifndef GAME_WON_STATE_H
#define GAME_WON_STATE_H

#include "State.h"


class Game_Won_State : public State
{
public:

    Game_Won_State();

    /* Updates Gameover-screen */
    void update() override;

    /* Handles events for Gameover-screen */
    void handle(sf::Event event) override;

    /* Renders Gameover-screen */
    void render(sf::RenderTarget & target) override;

    /* Checks which state is next */
    int get_next_state() override;

private:

    /* Game won */
    sf::Text game_won_text{};
    sf::Font game_won_font{};

    sf::Text congrats_text{};

    /* Instructions */
    sf::Text instruction_text{};
    sf::Font instruction_font{};

    /* For get_next_state() - initialized as false in construcor */
    bool play_again;
    bool exit_game;

};

#endif //GAME_WON_STATE_H