#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
	std::cerr << "Usage: " << argv[0] << " TEXT [ARGUMENTS...]\n";
	return 1;
    }
}
