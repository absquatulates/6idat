// Notera: Denna lÃ¶sning krÃ¤ver C++17

#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include <string>
#include <iostream>

/* FÃ¶rvÃ¤ntad utskrift:

1 4
2 5
3 6

1.2 7
3.4 8
5.6 9

*/

int main()
{
    {
	std::vector<int> v1 { 1, 2, 3 };
	std::vector<std::string> v2 { "4", "5", "6", "7" };
	
	zip_iterator it { v1.begin(), v1.end(), v2.begin(), v2.end() };
	zip_iterator end { v1.end(), v1.end(), v2.end(), v2.end() };
	
	while (it != end)
	{
	    auto p = *it;
	    
	    std::cout << p.first << " " << p.second << std::endl;
	    ++it;
	}
    }

    std::cout << std::endl;
    
    {
	std::list<double> v1 { 1.2, 3.4, 5.6 };
	std::forward_list<int> v2 { 7, 8, 9 };
	
	zip_iterator it { v1.begin(), v1.end(), v2.begin(), v2.end() };
	zip_iterator end { v1.end(), v1.end(), v2.end(), v2.end() };
	
	while (it != end)
	{
	    auto p = *it;
	    
	    std::cout << p.first << " " << p.second << std::endl;
	    ++it;
	}
    }
}
