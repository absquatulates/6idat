// Notera: Denna lÃ¶sning krÃ¤ver C++17

#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include <string>
#include <iostream>

template <typename It1, typename It2>
class zip_iterator
{
public:

    zip_iterator(It1 begin1, It1 end1, It2 begin2, It2 end2)
	: begin1  { begin1 } , end1  { end1 },
	  begin2 { begin2 }, end2 { end2 }
    {
    }

    auto operator*() const
    {
	return std::make_pair(*begin1, *begin2);
    }

    bool operator==(zip_iterator const& other) const
    {
	if (begin1 == end1 && other.begin1 == other.end1)
	    return true;

	if (begin2 == end2 && other.begin2 == other.end2)
	    return true;
	
	return begin1 == other.begin1 && begin2 == other.begin2;
    }

    bool operator!=(zip_iterator const& other) const
    {
	return !(*this == other);
    }
    
    zip_iterator& operator++()
    {
	++begin1;
	++begin2;
	return *this;
    }

    zip_iterator operator++(int)
    {
	zip_iterator tmp { *this };
	++*this;
	return tmp;
    }
    
private:

    It1 begin1;
    It1 end1;
    
    It2 begin2;
    It2 end2;
    
};


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
