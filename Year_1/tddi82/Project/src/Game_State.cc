#include "Game_State.h"
#include "Power_Up.h"

#include <cmath>

Game_State::Game_State() : game_over{false}, game_won{false} {
    init();
}

std::vector<std::pair<std::pair<int, int>, ENTITY_TYPE>> Game_State::load_map(
    std::ifstream& mapfile) {
    // Vector stores position and type of obstacles
    std::vector<std::pair<std::pair<int, int>, ENTITY_TYPE>> obstacles;
    int linenum{};
    for (std::string line; std::getline(mapfile, line);) {
        for (std::size_t i{}; i < line.size(); i++) {
            auto random_offset_x = rand() % WIDTH;
            auto random_offset_y = rand() % HEIGHT;
            if (tolower(line[i]) == 'i') {
                obstacles.push_back(
                    std::make_pair(std::make_pair(i + random_offset_x,
                                                  linenum + random_offset_y),
                                   ENTITY_TYPE::ISLAND));
            } else if (tolower(line[i]) == 'w') {
                obstacles.push_back(
                    std::make_pair(std::make_pair(i + random_offset_x,
                                                  linenum + random_offset_y),
                                   ENTITY_TYPE::SHIP_WRECK));
            }
        }
        linenum++;
    }
    mapfile.close();
    return obstacles;
}

void Game_State::init() {
    /* Initializing background */
    background_texture.loadFromFile("resources/Menu.jpg");
    if (!background_texture.loadFromFile("resources/Menu.jpg"))
    {throw std::invalid_argument("Unable to load background (Menu.jpg)");}
    background.setTexture(background_texture);

    Entities.clear();
    make_entities();

    /* Generate obstacles */
    std::ifstream mapfile("resources/obstacles.txt");
    auto obstacles = load_map(mapfile);
    for (auto obstacle : obstacles) {
        auto obstacle_pos = std::make_pair(obstacle.first.first + 50,
                                           obstacle.first.second + 50);
        auto obstacle_type = obstacle.second;
        auto obstacle_entity = std::make_shared<Obstacle>(
            obstacle_pos, Hitbox{100, 50, 50, 50}, obstacle_type);
        Entities.push_back(obstacle_entity);
    }

}

void Game_State::make_entities() {
    auto player = std::make_shared<Player>(std::make_pair(100, 100));
    auto enemy1 = std::make_shared<Enemy>(std::make_pair(300, 300), *player, ENEMY_SEEKER);
    auto enemy2 = std::make_shared<Enemy>(std::make_pair(800, 700), *player, ENEMY_TANKER);
    auto npc1 = std::make_shared<Npc>(std::make_pair(500, 500), NPC_SHIP);
    auto npc2 = std::make_shared<Npc>(std::make_pair(700, 100), NPC_SHIP);
    auto npc3 = std::make_shared<Npc_Shooter>(std::make_pair(300, 400), NPC_SHOOTER_SHIP, Entities);
    auto shield = std::make_shared<Shield>(*player);
    auto speed = std::make_shared<Speed_Up>(*player);
    Entities.push_back(player);
    Entities.push_back(enemy1);
    Entities.push_back(enemy2);
    Entities.push_back(npc1);
    Entities.push_back(npc2);
    Entities.push_back(npc3);
    Entities.push_back(shield);
    Entities.push_back(speed);
}

/* Checks how many Enemies is left, if 0 the game ends */
void Game_State::EnemiesLeft(){
    int enemies{};
    for( auto& entity : Entities){
        if (std::dynamic_pointer_cast<Enemy>(entity))
        {enemies++;}
    }
    if (enemies == 0 ) game_won = true;

}

void Game_State::NpcsLeft(){
    int npcs{};
    for( auto& entity : Entities){
        if (std::dynamic_pointer_cast<Npc>(entity))
        {npcs++;}
    }
    if (npcs == 0 ) game_over = true;
}

void Game_State::update() {
    /* Updates all Entities */
    for (auto entity : Entities) {
        // If entity is player or enemy
        if (entity->get_type() == ENTITY_TYPE::PLAYER ||
            entity->get_type() == ENTITY_TYPE::ENEMY  ||
            entity->get_type() == ENTITY_TYPE::NPC_SHOOTER){
            entity->update(newEntities);
        } else {
            entity->update();
        }
    }

    /* Add new entities to Entities */
    Entities.insert(Entities.end(), newEntities.begin(), newEntities.end());
    newEntities.clear();

    collisionHandler();
    isAliveHandler(); 
    EnemiesLeft();
    NpcsLeft();
}

void Game_State::isAliveHandler() {
    // Remove out-of-bounds and dead cannonballs/pointers
    for (auto it = Entities.begin(); it != Entities.end();) {
        if (*it == nullptr || !(*it)->isAlive()) {
            if((*it)->get_type() == ENTITY_TYPE::PLAYER) {
                game_over = true;
            }
            it = Entities.erase(it);
        } else {
            ++it;
        }
    }
}

void Game_State::collisionHandler() {
    for (auto first_it = Entities.begin(); first_it != Entities.end() - 1;
         ++first_it) {
        for (auto last_it = first_it + 1; last_it != Entities.end();
             ++last_it) {
            if ((*first_it)->collide(**last_it)) {
                (*first_it)->handleCollide((*last_it).get());
                (*last_it)->handleCollide((*first_it).get());
            }
        }
    }
}

void Game_State::handle(sf::Event event) { //används den här??
    /* Handle input for Player instance */
    for (auto& entity : Entities) {
        std::shared_ptr<Player> player =
            std::dynamic_pointer_cast<Player>(entity);
        if (player) {
            player->handleInput(event);
        }
    }

    //auto mouse_position = sf::Mouse::getPosition(window);
    /* Debug keys */
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            /* J: Adds a enemy entity to the game */
            case sf::Keyboard::Key::J:
                // TODO: Add enemy here to test
                break;
            default:
                break;
        }
    }
}

void Game_State::render_help_text(sf::RenderTarget& target) {
    sf::Text help_text;
    sf::Font font;
    font.loadFromFile("resources/font.ttf");
    help_text.setFont(font);
    help_text.setString(
        "Keys: \n\
    WASD & Space");
    help_text.setFillColor(sf::Color::Black);
    help_text.setPosition(0, 0);
    target.draw(help_text);
}

void Game_State::render_player_health(sf::RenderTarget& target, int health) {
    sf::Text health_text;
    sf::Font font;
    font.loadFromFile("resources/font.ttf");
    health_text.setFont(font);
    health_text.setString("Health: " + std::to_string(health * 10) + "%");
    health_text.setFillColor(sf::Color::Red);
    int text_width = health_text.getGlobalBounds().width;
    int text_height = health_text.getGlobalBounds().height;
    /* Bottom right */
    health_text.setPosition(WIDTH - text_width - 20, HEIGHT - text_height - 20);
    target.draw(health_text);
}

void Game_State::render_player_speed(sf::RenderTarget& target, double speed) {
    sf::Text speed_text;
    sf::Font font;
    font.loadFromFile("resources/font.ttf");
    speed_text.setFont(font);
    speed_text.setString("Max engine power: " + std::to_string(static_cast<int>(speed * 100)) + "%");
    speed_text.setFillColor(sf::Color::Green);
    int text_width = speed_text.getGlobalBounds().width;
    int text_height = speed_text.getGlobalBounds().height;
    /* Bottom right above health */
    speed_text.setPosition(WIDTH - text_width - 20, HEIGHT - text_height - 40);
    target.draw(speed_text);
}

void Game_State::render(sf::RenderTarget& target) {

    target.draw(background);

    render_help_text(target);

    /* Renders entities */
    for (auto& entity : Entities) {
        entity->render(target);
        if (entity->get_type() == ENTITY_TYPE::PLAYER) {
            auto player = std::dynamic_pointer_cast<Player>(entity);
            render_player_health(target, player->get_health());
            render_player_speed(target, player->get_speed());
        }
    }
}

int Game_State::get_next_state() {
    if (game_over) {
        game_over = false;
        init();
        return GAME_OVER_STATE;
    } 
    else if (game_won) {
        game_won = false;
        init();
        return GAME_WON_STATE;
    }
    else {
        return GAME_STATE;
    }
}