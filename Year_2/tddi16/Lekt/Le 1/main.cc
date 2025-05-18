#include <vector>


void sort(std::vector<int>& v)
{
    for (int i{}; i <v.size(); i++)
        std::swap(v.at(i), v.at(i+1));
}



int main()
{
    
}