#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"


class Menu_State : public State
{
public:

    /**
     * Constructor for Menu_State
     */
    Menu_State();

    /* Updates Menu-state */
    void update() override;
    /* Handles events for Menu-state */
    void handle(sf::Event event) override;
    /* Renders Menu-state */
    void render(sf::RenderTarget & target) override;
    /* Checks which state is next */
    int get_next_state() override;

private:

    bool play;

    sf::Text title_text{};
    sf::Font title_font{};
    sf::Text start_text{};
    sf::Font font{};


    sf::SoundBuffer selection_buffer{};
    sf::Sound selection_sound{};
    
    

};





#endif //MENU_STATE_H