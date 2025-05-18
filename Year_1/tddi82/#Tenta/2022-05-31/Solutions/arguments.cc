#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>

int main(int argc, char** argv)
{

    if (argc < 2)
    {
	std::cerr << "Usage: " << argv[0] << " TEXT [ARGUMENTS...]\n";
	return 1;
    }
    
    std::ifstream ifs { argv[1] };

    std::vector<std::string> text;
    
    std::string word;
    while (ifs >> word)
    {
	text.push_back(word);
    }

    std::map<std::string, std::string> arguments { };
    for (int i = 0; i + 2 < argc; ++i)
    {
	std::string key { "#" + std::to_string(i) };
	arguments[key] = argv[i + 2];
    }

    for (std::string& word : text)
    {
	if (word.front() == '#')
	{
	    auto it = arguments.find(word);
	    if (it == arguments.end())
	    {
		std::cerr << "Argument not set for " << word << std::endl;
		return 2;
	    }
	    word = it->second;
	}
	std::cout << word << " ";
    }
    std::cout << std::endl;
}
