// Cplusplus_O8.4
// hugho678: Samarbetat med carbj841, Carl Björlin, samma program

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

#include "hero_handling.h"
#include "register_handling.h"

using namespace std;

int menu()
{
  int choice{};

  cout << "Welcome to Hero Matchmaker 3000!\n";
  cout << "1) Add new hero to register file\n";
  cout << "2) Find matching heroes\n";
  cout << "3) Quit program\n";

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

int main(int argc, char *argv[])
{
  int choice;
  register_type heroes;
  string filepath = argv[1];

  if (argc != 2)
  {
    cout << "Incorrect number of arguments!\n"
         << "Usage: " << filepath << " REGISTERFILE" << endl;
  }
  else
  {
    ifstream infile;

    infile.open(filepath);
    readfile(infile, heroes);

    choice = menu();
    switch (choice)
    {
    case 1:
      add_hero(filepath, heroes);
      break;

    case 2:
      //    Matching_hero()
      break;

    case 3:
      cout << "Terminating Hero Matchmaker 3000!\n";
      break;
    }
  }
  return 0;
}
