#ifndef ASTROID_H
#define ASTROID_H


//STRUCTS
struct Radius
{
    double radie;
};

struct Point
{
    int x;
    int y;
};

//CLASSES
class Object
{
public:
    Object(Point pos);
    virtual ~Object() = default;
    virtual bool collide(Object* o) = 0;

protected:
    Point position;
};

class Enemy : public Object
{
public:
    Enemy(Point pos, int damage);
    bool collide(Object* o) override;

protected:
    int damage{3};
};

class Player : public Object
{
public:
    Player(Point pos, int hp);
    bool collide(Object* o) override;
    void hit();

private:
    int hp{10};
    void die();
};

class Astroid : public Enemy
{
public:
    Astroid(Point pos, int damage, Point direction);
    void charge();

private:
    Point direction;
};

class Ufo : public Enemy
{
public:
    Ufo(Point pos, int damage);
    void locate();

private:
    Radius radius;
    bool active;

    void shoot();
    void activate();
};



#endif