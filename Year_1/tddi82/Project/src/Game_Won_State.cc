#include "Game_Won_State.h"
#include <string>
#include <stdexcept>

Game_Won_State::Game_Won_State()
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
    
    /* Initializing Game won font and text */
    std::string game_won_file = "resources/Minecraft.ttf";
    if (!game_won_font.loadFromFile(game_won_file)) //Checking if file is accessible
    {throw std::invalid_argument("Unable to load font (Minecraft.ttf).");}
    game_won_text = sf::Text{"Game Won", game_won_font, 100};

    /* Initializing congrats text */
    congrats_text = sf::Text{"You've killed all enemies", game_won_font, 30};
}

void Game_Won_State::update() {}

void Game_Won_State::handle(sf::Event event)
{
     if (event.type == sf::Event::KeyPressed)
     {
        if (event.key.code == sf::Keyboard::Key::Return)
        {play_again = true;} //Next state = GAME_STATE
        else if  (event.key.code == sf::Keyboard::Key::Escape)
        {exit_game = true;} //Closes window
        
        //else, next state = Game_Won_State
     }
}

void Game_Won_State::render(sf::RenderTarget & target)
{
    auto instruction_bounds{instruction_text.getGlobalBounds()};
    auto game_won_bounds{game_won_text.getGlobalBounds()};
    auto congrats_bounds(congrats_text.getGlobalBounds());
    auto size{target.getSize()}; //Window size

    instruction_text.setPosition ((size.x - instruction_bounds.width) / 2,
                      (size.y - instruction_bounds.height) / 1.1);

    game_won_text.setPosition ((size.x - game_won_bounds.width) / 2,
                                (size.y - game_won_bounds.height) / 3);
    
    congrats_text.setPosition ((size.x - congrats_bounds.width) / 2,
                                (size.y - congrats_bounds.height) / 2);

    target.draw(background);
    target.draw(instruction_text);
    target.draw(game_won_text);
    target.draw(congrats_text); 
}

int Game_Won_State::get_next_state()
{
    if (play_again)
    {
        play_again = false;
        return GAME_STATE;
    }
    else
    {
        return GAME_WON_STATE;
    }
}