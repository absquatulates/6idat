#include "ghost.h"
#include "given.h"
#include "main.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

// Kommentar: Er teckenkodning är inte rätt. åäö blir nonsenstecken. Se till att lära er hur man
//   byter teckenkodning i er textredigerare.

/*
  Ledning och Tips:

  - Modifiera stukturen till en header-fil och en implementationsfil
  - Ut�ka 'run()' och 'draw_map()' med �vrig funktionalitet.
  - L�gg alla sp�ken i en l�mplig beh�llare som en datamedlem.
  - Bryt ut stora kodblock till egna funktioner.
  - Anv�nd hj�lpfunktioner f�r att undvika duplicering av kod.
  - T�nk p� att varje funktion inte borde vara l�ngre �n 25 rader.
 */

Ghost_Tester::Ghost_Tester()
    : pacman {}
{
    ghosts.push_back(new Blinky{pacman, {2,8}, {WIDTH-1, HEIGHT-1}, "red"});
    ghosts.push_back(new Pinky{pacman, {13,9}, {0, HEIGHT-1}, "pink"});
    ghosts.push_back(new Clyde{pacman, {8,2}, {0,0}, "orange",6});
}

void Ghost_Tester::run()
{
    int n {};
    for (int i{}; i < ghosts.size(); i++)
    {
        if (ghosts.at(i)->get_color().at(0) == 'r') //Hittar blinky...
        {
            n = i;
        }
        
    }    
    Blinky* blinky{dynamic_cast<Blinky*>(ghosts.at(n))};
    
    while(true)
    {
        draw_map();
        cout << "> ";

        string line {};
        getline(cin, line);
        istringstream iss {line};
    
        string command {};
        iss >> command;
        Point new_xy {};
        iss >> new_xy.x >> new_xy.y;

        if (command == "pos")
        {
            pacman.set_position(new_xy);
        }
        else if (command == "dir")
        {
            pacman.set_direction(new_xy);
        }
        else if (command == "scatter")
        {
            scatter = true;   
        }
        else if (command == "chase")
        {
            scatter = false;
        }
        else if (command == "anger")
        {
            blinky->set_angry(true);
        }
        else if (command == "calm")
        {
            blinky->set_angry(false);
        }
        else if (command == "quit")
        {
            break;
        }
        else
        {
            for (Ghost* ghost : ghosts)
            {
            if (command == (ghost->get_color()))
                {
                    ghost->set_position(new_xy);
                }
            }
        }
    }
}

std::string Ghost_Tester:: to_draw(Point const& curr_pos, std::vector<Ghost*> ghosts)
    {
        std::string to_draw{"  "};
        Blinky* blinky{dynamic_cast<Blinky*>(ghosts.at(0))};
        Pinky* pinky{dynamic_cast<Pinky*>(ghosts.at(1))};
        Clyde* clyde{dynamic_cast<Clyde*>(ghosts.at(2))};

        if (pacman.get_position() == curr_pos)
        {
            to_draw[1] = '@';
        }
        for (Ghost* ghost : ghosts)
        {
            if (ghost->get_position() == curr_pos)
            {
                to_draw[0] = toupper(ghost->get_color().at(0));    
            }
            if ((ghost->get_scatter_point() == curr_pos) and scatter)
            {
                to_draw[0] = tolower(ghost->get_color().at(0));    
            }
            if ((ghost->get_chase_point() == curr_pos) and !scatter)
            {
                to_draw[0] = tolower(ghost->get_color().at(0));    
            }           
        }
        return to_draw;
    }

void Ghost_Tester::draw_map()
{
    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+\n";

    for (int y {HEIGHT - 1}; y >= 0; --y) 
    {
        cout << "|";
        for (int x {}; x < WIDTH; ++x) 
        {
            cout << to_draw( Point{x,y}, ghosts);
        }            
        cout << "|\n";
    }
    
    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+" << endl;
}

int main()
{                      
    Ghost_Tester gt {};
    gt.run();
    return 0;
}
