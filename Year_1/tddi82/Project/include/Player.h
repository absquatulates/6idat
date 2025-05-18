#ifndef PLAYER_H
#define PLAYER_H

#include "Ship.h"
#include "Canonball.h"
#include "Game_State.h"
#include "Constants.h"

#include <math.h>
#include <memory>

class Player : public Ship {
    public:
        /**
         * @param pos spawn position
         */
        Player(std::pair<int,int> const & pos);
        virtual ~Player() = default;
        /* Moves the player in the direction of the parameter */
        void update(std::vector<std::shared_ptr<Entity>> & d_e_v) override;

        /* Handles input from the player */
        void handleInput(sf::Event event);

    private:
        bool movingForward = false;
        bool movingBack = false;
        bool movingRight = false;
        bool movingLeft = false;
        bool shooting = false;

        sf::SoundBuffer selection_buffer{};
        sf::Sound selection_sound{};
};

#endif