#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "DynamicEntity.h"
#include "State.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Player.h"
#include "Constants.h"
#include "Power_Up.h"
#include "Npc.h"
#include "Npc_Shooter.h"

#include <memory>
#include <vector>

class Game_State : public State {
   public:
    Game_State();

    /* Updates Game-state */
    void update() override;
    /* Handles events for Game-state */
    void handle(sf::Event event) override;
    /* Renders Game-state */
    void render(sf::RenderTarget& target) override;
    /* Checks which state is next */
    int get_next_state() override;
    /* Loads map from file */
    std::vector<std::pair<std::pair<int, int>, ENTITY_TYPE>> load_map(
        std::ifstream& mapfile);
    
    /* Initializes Game-state */
    void init();
    /* Renders help text */
    void render_help_text(sf::RenderTarget& target);
    /* Renders player health */
    void render_player_health(sf::RenderTarget& target, int health);
    /* Renders player speed */
    void render_player_speed(sf::RenderTarget& target, double speed);

   private:
    bool game_over;
    bool game_won;
    std::vector<std::shared_ptr<Entity>> Entities{};
    std::vector<std::shared_ptr<Entity>> newEntities{};
    friend class Enemy;

    /*Handles collisions*/
    void collisionHandler();
    /*handles entities that are dead*/
    void isAliveHandler();

    void make_entities();
    void EnemiesLeft();
    void NpcsLeft();
};

#endif  // GAME_STATE_H