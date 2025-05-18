#include <vector>
#include <set>
#include <iostream>

template <typename Container>
class Split_Container
{
public:

    using value_type = std::vector<typename Container::value_type>;
    
    Split_Container(Container const& container, std::size_t groups)
        : container { container }, group_size { container.size() / groups }
    {
    }

    void set_groups(std::size_t groups)
    {
        group_size = container.size() / groups;
    }
    
    value_type get_group(std::size_t index) const
    {
        std::size_t start { index * group_size };
        value_type result {
            std::next(container.begin(), start),
            std::next(container.begin(), start + group_size)
        };
        return result;
    }

    std::size_t size() const
    {
        return container.size() / group_size;
    }
    
private:

    Container container;
    std::size_t group_size;
    
};

/* 

FÃ¶rvÃ¤ntad utmatning:

Group #1: 1 2 3 4 
Group #2: 5 6 7 8 
Group #3: 9 10 11 12 

Group #1: 1 2 3 
Group #2: 4 5 6 
Group #3: 7 8 9 
Group #4: 10 11 12 

Group #1: Mango Pineapple Papaya 
Group #2: Blueberries Blackberries Raspberries 
Group #3: Pear Plum Peach 
Group #4: Kiwi Passion fruit Lychee 

*/

template <typename Container>
void print_groups(Split_Container<Container> const& sv)
{
    for (std::size_t i { 0 }; i < sv.size(); ++i)
    {
        std::cout << "Group #" << (i + 1) << ": ";
        auto group { sv.get_group(i) };
        for (auto e : group)
        {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::set<int> v { 9, 8, 6, 1, 4, 7, 12, 2, 11, 3, 10, 5 };
    Split_Container<std::set<int>> sv { v, 3 };
    print_groups(sv);

    std::cout << std::endl;
    
    sv.set_groups(4);
    print_groups(sv);

    std::cout << std::endl;
    
    std::vector<std::string> fruits {
        "Mango", "Pineapple", "Papaya",
        "Blueberries", "Blackberries", "Raspberries",
        "Pear", "Plum", "Peach",
        "Kiwi", "Passion fruit", "Lychee"
    };

    Split_Container<std::vector<std::string>> sfruits { fruits, 4 };
    print_groups(sfruits);
}
