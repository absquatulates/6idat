#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "hero_handling.h"
#include "register_handling.h"

using namespace std;

void readfile(ifstream &infile, register_type &heroes)
{

  string line;

  while (getline(infile, line))
  {
    hero_type hero;
    stringstream ss{};
    int intrest{};

    ss << line;
    ss >> hero.name >> hero.age >> hero.weight >> hero.hair_color;

    while (ss >> intrest)
    {
      hero.intrests.push_back(intrest);
    }
    sort(hero.intrests.begin(), hero.intrests.end());
    heroes.hero_list.push_back(hero);
  }
  for (hero_type hero : heroes.hero_list)
  {
    cout << hero.toString() << endl;
  }
}

void add_hero(string &filepath, register_type &heroes)
{
  hero_type new_hero;
  int intrest{};
  string line;
  stringstream ss;

  cout << "Enter hero information: ";

  cin.ignore();
  getline(cin, line);

  ss.clear();
  ss.str(line);
  ss >> new_hero.name >> new_hero.age >> new_hero.weight >> new_hero.hair_color;

  while (ss >> intrest)
  {
    new_hero.intrests.push_back(intrest);
  }
  heroes.hero_list.push_back(new_hero);

  sort(heroes.hero_list.begin(), heroes.hero_list.end(), compareFirstLetter);

  saveToFile(filepath, heroes);
}

bool compareFirstLetter(const hero_type &hero1, const hero_type &hero2)
{
  return hero1.name < hero2.name;
}

void saveToFile(std::string &filepath, register_type &heroes)
{
  ofstream outfile(filepath, ios::out);

  for (hero_type hero : heroes.hero_list)
  {
    outfile << left << setw(11) << hero.name << left << setw(12) << hero.age << left << setw(8) << fixed << setprecision(2) << hero.weight << left << setw(12) << hero.hair_color;

    for (int i : hero.intrests)
    {
      outfile << right << setw(3) << i;
    }
    outfile << endl;
  }

  outfile.close();
}
