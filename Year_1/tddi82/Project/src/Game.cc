#include "Game.h"

Game::Game(std::string const& game_title, unsigned WIDTH, unsigned HEIGHT)
    : window {sf::VideoMode{WIDTH, HEIGHT}, game_title}, current_state{MENU_STATE},running{true}
{
    states.insert(std::pair<int, std::unique_ptr<State>> ({MENU_STATE, std::make_unique<Menu_State>()}));
    states.insert(std::pair<int, std::unique_ptr<State>> ({GAME_STATE, std::make_unique<Game_State>()}));
    states.insert(std::pair<int, std::unique_ptr<State>> ({GAME_OVER_STATE, std::make_unique<Game_Over_State>()}));
    states.insert(std::pair<int, std::unique_ptr<State>> ({GAME_WON_STATE, std::make_unique<Game_Won_State>()}));

}

void Game::start()
{
    sf::Clock clk{};
    sf::Event e;

    while (running)
    {

        handle_events(e);
        states.at(current_state) -> update();
        window.clear();
        states.at(current_state) -> render(window);
        window.display();
        current_state = states.at(current_state) -> get_next_state();
        delay(clk);
    }
}


void Game::handle_events(sf::Event e)
{
    
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed || 
            (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape))
        {
            running = false;
        }
        
        states.at(current_state) -> handle(e);
    }
}


void Game::delay(sf::Clock & clk) const
{
    sf::sleep(sf::milliseconds(1000.0/FPS) - clk.getElapsedTime());
    clk.restart();
}
