#include "Player.h"

/* Intital values for the player */
Hitbox hb = {50, 50, 70, 70};
double dir = -M_PI / 2;
double spd = 1.0;
int hp = 10;
int dmg = 1;

Player::Player(std::pair<int, int> const& pos)
    : Ship{pos, hb, dir, spd, hp, dmg, PLAYER_SHIP} {
        type = PLAYER;
        selection_buffer.loadFromFile("resources/shot_00.wav");
        selection_sound.setBuffer(selection_buffer);
    }

void Player::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::W:
                movingForward = true;
                break;
            case sf::Keyboard::A:
                movingLeft = true;
                break;
            case sf::Keyboard::S:
                movingBack = true;
                break;
            case sf::Keyboard::D:
                movingRight = true;
                break;
            case sf::Keyboard::Space:
                shooting = true;
                break;
            default:
                break;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::W:
                movingForward = false;
                break;
            case sf::Keyboard::A:
                movingLeft = false;
                break;
            case sf::Keyboard::S:
                movingBack = false;
                break;
            case sf::Keyboard::D:
                movingRight = false;
                break;
            default:
                break;
        }
    }
}

void Player::update(std::vector<std::shared_ptr<Entity>> & d_e_v) {
    if (movingForward) {
        move(forward);
    }

    if (movingLeft) {
        move(left);
    }

    if (movingBack) {
        move(back);
    }

    if (movingRight) {
        move(right);
    }

    if (shooting) {
        shooting = false;
        selection_sound.play();
        shoot(d_e_v);
    }

    DynamicEntity::update();
}
