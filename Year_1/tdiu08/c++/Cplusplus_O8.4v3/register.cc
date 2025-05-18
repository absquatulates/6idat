#include "register.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>


void read(std::ifstream& file, Register_Type& heroes)
{
    std::string line{};

    while (std::getline(file, line))
    {
        Hero_Type hero{};
        std::stringstream ss{};
        int interest{};

        ss << line;
        ss >> hero.name >> hero.year >> hero.weight >> hero.haircolor;

        while (ss >> interest)
        {
            hero.interests.push_back(interest);
        }
        std::sort(hero.interests.begin(), hero.interests.end());
        heroes.push_back(hero);
    }
}



//----------addHero----------//

Hero_Type inputHero()
{
    Hero_Type newHero;
    int interest{};
    std::string line;
    std::stringstream ss;
    std::cout << "Enter hero information:" << std::endl;

    std::getline(std::cin, line);
        ss.str(line);
        ss >> newHero.name >> newHero.year >> newHero.weight >> newHero.haircolor;

    while (ss >> interest)
        newHero.interests.push_back(interest);
    
    return newHero;
}


bool matchName(Hero_Type const& newHero, Register_Type const& heroes)
{
    bool match{false};
        for (int i{}; i < heroes.size(); i++)
        {
            if (newHero.name == heroes.at(i).name)
            {
                match = true;
                break;
            }
        }
    return match;
}


void writeToFile(Hero_Type const& newHero, Register_Type & heroes, std::string const& filename)
{
    std::ofstream outfile{filename};

    heroes.push_back(newHero);
    std::sort(heroes.begin(), heroes.end());
    if (outfile.is_open())
    {
        for (int i{}; i < heroes.size(); i++)
            outfile << heroes.at(i) << std::endl;

        std::cout << "The hero was added to the register on file " << filename << std::endl;
    }
}


void addHero(Register_Type & heroes,std::string const& filename)
{
    while (true)
    {
        Hero_Type newHero{inputHero()};

        if (!matchName(newHero, heroes))
        {

            writeToFile(newHero, heroes, filename);
            break;
        }
        else
            std::cout << "Hero already in register. ";    
    }
}



//----------FindMatchingHeroes----------//

Register_Type makeMatchList(Register_Type const& heroes, std::vector<int> const& newinterests)
{
    Register_Type matchingHeroes{};
    for (int i{}; i < heroes.size(); i++)
    {
        for (int j{}; j < heroes.at(i).interests.size(); j++)
        {
            for (int n{}; n < newinterests.size(); n++)
            {
                if (heroes.at(i).interests.at(j) == newinterests.at(n))
                    matchingHeroes.push_back(heroes.at(i));
            }
        }
    }

    if (matchingHeroes.size() > 1)
        matchingHeroes = removeDuplicates(matchingHeroes);

    return matchingHeroes;
    
}


void printHeroes(Register_Type const& heroes)
{
    std::cout << "There are " << heroes.size() << " matching heroes." << std::endl << 
                 std::left << std::setw(11) << "Hero name" << std::left << std::setw(12) << "Birth year" << std::left << std::setw(8) << 
                 "Weight" << std::left << std::setw(12) << "Hair color" << std::right << std::setw(3) << "Interests" << std::endl <<
                 "====================================================" << std::endl;

    if (heroes.size() > 0)
    {
        for (int i{}; i < heroes.size(); i++)
            std::cout << heroes.at(i) << std::endl;
    }
}


std::vector<int> getinterests()
{
    std::vector<int> interests{};
    bool valid{};
    int interest{};

    while(!valid)
    {
        interests = {};
        std::string line{};
        std::getline(std::cin, line);
        std::stringstream ss{line};

        while (ss >> interest)
        {
            if (interest > 0 && interest < 16 )
            {
                interests.push_back(interest);
                valid = true;
            }        
        }
        if (valid)
            break;
    }
    return interests;
}


Register_Type removeDuplicates(Register_Type const& matchingHeroes)
{
    Register_Type newMatchingHeroes{};

    int i{};
    do
    {
        if (matchingHeroes.at(i).name != matchingHeroes.at(i+1).name)
        newMatchingHeroes.push_back(matchingHeroes.at(i));
        i++;
    } while (i != (matchingHeroes.size()-1));

    if (matchingHeroes.at(i).name != newMatchingHeroes.at(newMatchingHeroes.size()-1).name)
        newMatchingHeroes.push_back(matchingHeroes.at(i));
    return newMatchingHeroes;
}

void findMatchingHeroes(Register_Type const& heroes)
{
    std::vector<int> newinterests{getinterests()};
    Register_Type matchingHeroes{makeMatchList(heroes, newinterests)};
    printHeroes(matchingHeroes);
}