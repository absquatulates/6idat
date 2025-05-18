#ifndef GHOST_H
#define GHOST_H

#include <string>
#include "given.h"

// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka.
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   Malte.Nilsson@liu.se

//ALLA kommentarer/Kompletteringar gäller i denna fil.
// tog bort vissa KLAR kommentarer då detta inte var fallet för de som är kvar


// Kommentar: Medlemmar som inte behöver kommas åt från en härledd klass ska vara privata.
    //klar? 21/3

// Kommentar: Pinky::get_chase_point() går att implementera utan if-satser.
    //KLAR 21/3

// Kommentar: Alla datamedlemmar ska initieras i datamedlemsinitieringslistan. 
// inte i .h filen
// Ta även bort måsvingarna i .h filen då de även initieras här ifall det missas i datamedlemsinitieringslistan 
//inte klar
    //KLAR 21/3
 

//Komplettering: Första röda spöket antas vara Blinky.
// Alla spöken måste dynamic_castas och lyckas omvandlingen så går det att anropa set_angry.
// iterera över listan av spöken och använd dynamic_cast för att "lista" ut vilket spöke som är Blinky
    //KLAR 21/3


//Kommentar ta bort oanvända variabler i main.cc 
// t.ex. Clyde* clyde
    //KLAR 21/3

//Komplettering. Funktioner med variabler som är konstanta ska markeras som konstanta.
    //KLAR 21/3


class Ghost
{
 public:
    Ghost(Pacman& pacman, Point const& pos, Point const& scatter_pos, std::string const& color);
    virtual ~Ghost() = default;
    std::string get_color() const;
    Point get_position() const;
    void set_position(Point& new_pos);
    virtual Point get_scatter_point() const;
    virtual Point get_chase_point() const = 0;

 protected:
    Pacman& pacman;
    Point pos;
    Point scatter_pos;
    std::string color;

};

class Blinky : public Ghost
{
public:
    using Ghost::Ghost;
    Point get_chase_point() const override;
    Point get_scatter_point() const override;
    void set_angry(bool angry);
private:
    bool angry{};
};

class Pinky : public Ghost
{
public:
    using Ghost::Ghost;
    Point get_chase_point() const override;
};

class Clyde : public Ghost
{
public:
    Clyde(Pacman& pacman, Point const& pos, Point const& scatter_pos, std::string const& color, int const& dis);
    Point get_chase_point() const override;
private:
    int dis;
};

#endif