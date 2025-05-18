#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "Entity.h"

enum movdir { forward, left, right, back };

class DynamicEntity : public Entity {
   public:
    /**
     * @param pos spawn position
     * @param hb hitbox dimensions
     */
    DynamicEntity(std::pair<int, int> const& pos, Hitbox const& hb);

    /**
     * @param pos spawn position
     * @param hb hitbox dimensions
     * @param dir direction
     * @param speed inital speed
     */
    DynamicEntity(std::pair<int, int> const& pos, Hitbox const& hb,
                  double const dir, double const speed, std::pair<float, float> velocity = {0, 0});

    /**
     * @returns direction
     */
    double get_dir() const;

    /**
     * sets speed
     * @param new_speed new speed
     */
    void set_speed(double new_speed);

    /**
     * @returns speed
    */
    double get_speed() const;

    /**
     * updates position based on velocity
     */
    void update() override;

   protected:

    double direction;  // direction entity is going in, 0 = right
    double speed;                         // entity speed
    std::pair<float, float> velocity;  // entity velocity vector


    /**
     * changes position based on direction and speed
     * @param movement enum describing how to move
     */
    void move(movdir const& movement);
};

#endif