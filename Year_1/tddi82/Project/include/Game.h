#ifndef GAME_H
#define GAME_H

#include "Menu_State.h"
#include "Game_State.h"
#include "Game_Over_State.h"
#include "Game_Won_State.h"
#include "Constants.h"

#include <string>
#include <map>
#include <utility>
#include <memory>

class Game
{
public:
    /**
     * @param game_title title of the game
     * @param WIDTH width of the window
     * @param HEIGHT height of the window
     */
    Game(std::string const& game_title, unsigned WIDTH, unsigned HEIGHT);
    
    /**
     * Starts the game
     */
    void start();

private:

    sf::RenderWindow window;
    sf::VideoMode mode{sf::VideoMode::getDesktopMode()};

    int current_state;
    bool running;

    std::map<int, std::unique_ptr<State>> states{};

    /**
     * @param e event to handle
     */
    void handle_events(sf::Event e);

    /**
     * @param clk clock to delay
     */
    void delay(sf::Clock & clk) const;
};
















#endif //GAME_H