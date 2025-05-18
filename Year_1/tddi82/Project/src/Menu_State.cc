#include "Menu_State.h"
#include <string>
#include <stdexcept>


Menu_State::Menu_State()
    : play{false}
{

    /* Initializing background */
    background_texture.loadFromFile("resources/Menu.jpg");
    if (!background_texture.loadFromFile("resources/Menu.jpg"))
    {throw std::invalid_argument("Unable to load background (Menu.jpg)");}
    background.setTexture(background_texture);

    std::string file = "resources/font.ttf";
    if (!font.loadFromFile(file))
    {throw std::invalid_argument("Unable to load font.");}
    start_text = sf::Text{"Press <ENTER> to play", font, 20};
    std::string title_file = "resources/Minecraft.ttf";
    if (!title_font.loadFromFile(title_file))
    {throw std::invalid_argument("Unable to load font (Minecraft.ttf).");}  
    title_text = sf::Text{"World of Ships", title_font, 100};
    
    selection_buffer.loadFromFile("resources/select.wav");
    selection_sound.setBuffer(selection_buffer);
}

void Menu_State::update()
{
}

void Menu_State::handle(sf::Event event)
{


    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Return)
        {

            selection_sound.play();
            play = true;
        }
        
    }
}

void Menu_State::render(sf::RenderTarget & target)
{
    auto bounds { start_text.getGlobalBounds () };
    auto size   { target.getSize () };

    auto title_bounds { title_text.getGlobalBounds () };
    
    start_text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 1.1);

    title_text.setPosition ((size.x - title_bounds.width) / 2,
                            (size.y - title_bounds.height) / 10);
    
    sf::Texture menu_texture;
    menu_texture.loadFromFile("resources/Menu.jpg");
    sf::Sprite menu_background(menu_texture);
 
    sf::Texture menu_boat_texture;
    menu_boat_texture.loadFromFile("resources/menu_boat.png");
    sf::Sprite menu_boat(menu_boat_texture);
    menu_boat.setScale(0.45, 0.5);
    menu_boat.setPosition((size.x - bounds.width) / 2.2,
                          (size.y - bounds.height) / 4);



    target.draw(menu_background);
    target.draw(menu_boat);
    target.draw(start_text);
    target.draw(title_text);




}

int Menu_State::get_next_state()
{
    if (play)
    {
        play = false;
        return GAME_STATE;
    }
    else
    {
        return MENU_STATE;
    }
}

