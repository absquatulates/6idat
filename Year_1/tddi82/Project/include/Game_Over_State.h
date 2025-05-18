#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "State.h"

class Game_Over_State : public State
{
public:

    Game_Over_State();

    /* Updates Gameover-screen */
    void update() override;

    /* Handles events for Gameover-screen */
    void handle(sf::Event event) override;

    /* Renders Gameover-screen */
    void render(sf::RenderTarget & target) override;

    /* Checks which state is next */
    int get_next_state() override;

private:

    /* Game over */
    sf::Text game_over_text{};
    sf::Font game_over_font{};
    
    sf::Text dead_text{};

    /* Instructions */
    sf::Text instruction_text{};
    sf::Font instruction_font{};

    /* For get_next_state() - initialized as false in construcor */
    bool play_again;
    bool exit_game;

};

#endif //GAME_OVER_STATE_H