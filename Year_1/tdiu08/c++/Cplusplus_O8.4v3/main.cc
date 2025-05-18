// wilhe308: Samarbetat med hugho678, Hugo Holmberg, samma program

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "hero.h"
#include "register.h"


int menu()
{
    int sel{};

    std::cout << "1) Add new hero to register file" << std::endl
              << "2) Find matching heroes" << std::endl
              << "3) Quit program" << std::endl;

    do
    {
        std::cout << "Select: ";
        std::cin >> sel;
    } while (sel < 1 || sel > 3);
    
    return sel;
}


int main(int argc, char *argv[])
{

    if (argc != 2 )
    {
        std::cout << "Incorrect number of arguments!" << std::endl
                  << "Usage: ./executable_program REGISTERFILE" << std::endl;
    }
    else
    {
        std::string filename{argv[1]};
        std::cout << "Welcome to Hero Matchmaker 3000!" << std::endl;
        
        while (true)
        {
            Register_Type heroes{};
            std::ifstream file{filename};
            int sel{};
            read(file, heroes);
            sel = menu();

            switch (sel)
            {
            case 1:
                std::cin.ignore(1000, '\n');
                addHero(heroes, filename);
                break;
            case 2:
                std::cout << "Enter your interests (at least one between 1 and 15): ";
                findMatchingHeroes(heroes);
                break;
            case 3:
                std::cout << "Terminating Hero Matchmaker 3000!" << std::endl;
                return 0;
            }
        } 
    }
}
