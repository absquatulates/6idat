// Cplusplus_O8.4
// hugho678: Samarbetat med carbj841, Carl Björlin, samma program

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <fstream>


#include "hero_handling.h"
#include "register_handling.h"

using namespace std;


//register_handling.cc


//hero_handling.cc

void add_hero(register_type & heroes)
{
    hero_type hero;
    int I;
    while (true)
    {
        cout << "Enter hero information: " << endl;

        cin >> hero.name >> hero.age >> hero.weight >> hero.hair_color;
        while (cin >> I)
        {
            hero.intrests.push_back(I);
        }

        for (int i {}; i < heroes.hero_list.size(); i++)
        {
            if (hero.name == heroes.hero_list.at(i).name)
            {
                cout << "Hero already in register.";
                break;
            }
            else
            {
                heroes.hero_list.push_back(hero);
            }
        }
    }   
}

// main.cpp

int menu()
{
    int choice {};


    cout << "Welcome to Hero Matchmaker 3000!\n";
    cout << "1) Add new hero to register file\n";
    cout << "2) Find matching heroes\n";
    cout << "3) Quit program" << endl;
 
    while (true)
    {
    cout << "Select: ";
    cin >> choice;
        if (!(choice < 1 || choice > 3))
        {
            break;
        }
    }
    return choice;
}


register_type readfile(char *argv[])
{
  hero_type hero; 
  string line;
  register_type heroes;
  ifstream infile(argv[1]);
  int intrest {};

  while (getline(infile, line))
  {

    stringstream ss(line);


    ss << line;
    ss >> hero.name >> hero.age >> hero.weight >> hero.hair_color;

    while (ss >> intrest)
    {
        hero.intrests.push_back(intrest);
    }
    sort(hero.intrests.begin(), hero.intrests.end());
    heroes.hero_list.push_back(hero);
    hero.intrests = {};
  }
    return heroes;
}

int main(int argc, char *argv[])
{
    register_type heroes;
    int choice {};
    hero_type hero;

    if (argc != 2)
    {
        cout << "Incorrect number of arguments!\n";
        cout << "Usage: " << argv[0] << " REGISTERFILE" << endl;
    }
    else
    {

        heroes = readfile(argv);
        cout << heroes.hero_list.at(0).name << endl;
        choice = menu();

        switch (choice)
    {
        case 1:
            add_hero(heroes);
            break;
        case 2:
            break;
        case 3:
            cout << "Terminationg Hero Matchmaker 3000!";
        break;
    }

    }  
}
  
 