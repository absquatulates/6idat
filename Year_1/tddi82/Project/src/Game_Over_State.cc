#include "Game_Over_State.h"
#include <string>
#include <stdexcept>

Game_Over_State::Game_Over_State()
    : play_again{false}, exit_game{false}
{
    /* Initializing background */
    background_texture.loadFromFile("resources/Menu.jpg");
    if (!background_texture.loadFromFile("resources/Menu.jpg"))
    {throw std::invalid_argument("Unable to load background (Menu.jpg)");}
    background.setTexture(background_texture);

    /* Initializing instruction font and text */
    std::string instruction_file = "resources/font.ttf";
    if (!instruction_font.loadFromFile(instruction_file)) //Checking if file is accessible
    {throw std::invalid_argument("Unable to load font (font.ttf).");}
    instruction_text = sf::Text{"Press <ESC> to exit or <ENTER> to play again", instruction_font, 16};
    
    /* Initializing Game over font and text */
    std::string game_over_file = "resources/Minecraft.ttf";
    if (!game_over_font.loadFromFile(game_over_file)) //Checking if file is accessible
    {throw std::invalid_argument("Unable to load font (Minecraft.ttf).");}
    game_over_text = sf::Text{"Game Over", game_over_font, 100};

    /* Initializing Dead text*/
    dead_text = sf::Text{"You died", game_over_font, 30};

}

void Game_Over_State::update() {}

void Game_Over_State::handle(sf::Event event)
{
     if (event.type == sf::Event::KeyPressed)
     {
        if (event.key.code == sf::Keyboard::Key::Return)
        {play_again = true;} //Next state = GAME_STATE
        else if  (event.key.code == sf::Keyboard::Key::Escape)
        {exit_game = true;} //Closes window
        
        //else, next state = GAME_OVER_STATE
     }
}

void Game_Over_State::render(sf::RenderTarget & target)
{
    auto instruction_bounds{instruction_text.getGlobalBounds()};
    auto game_over_bounds{game_over_text.getGlobalBounds()};
    auto dead_bounds(dead_text.getGlobalBounds());

    auto size{target.getSize()}; //Window size

    instruction_text.setPosition ((size.x - instruction_bounds.width) / 2,
                      (size.y - instruction_bounds.height) / 1.1);

    game_over_text.setPosition ((size.x - game_over_bounds.width) / 1.9,
                                (size.y - game_over_bounds.height) / 3);
    
    dead_text.setPosition ((size.x - dead_bounds.width) / 2,
                                (size.y - dead_bounds.height) / 2);

    target.draw(background);
    target.draw(instruction_text);
    target.draw(game_over_text);
    target.draw(dead_text);
}

int Game_Over_State::get_next_state()
{
    if (play_again)
    {
        play_again = false;
        return GAME_STATE;
    }
    else
    {
        return GAME_OVER_STATE;
    }
}




