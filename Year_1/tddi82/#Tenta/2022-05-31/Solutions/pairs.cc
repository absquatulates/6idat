#include <vector>
#include <list>
#include <iostream>
#include <cctype>
#include <iterator>

template <typename It>
auto get_pairs(It begin, It end)
{
    using value_type = typename It::value_type;
    
    std::vector<std::pair<value_type, value_type>> pairs { };
    for (It current { begin }; current != end; ++current)
    {
	for (It next { std::next(current) }; next != end; ++next)
	{
	    pairs.emplace_back(*current, *next);
	}
    }
    return pairs;
}

int main()
{

    std::cout << "==== Testfall #1 ====" << std::endl;
    
    // Enkelt testfall
    std::vector<int> v1 { 1, 2, 3, 4 };
    auto v1_pairs { get_pairs(v1.begin(), v1.end()) };

    // v1_pairs innehÃ¥ller par, sÃ¥ vi loopar Ã¶ver den
    for (std::pair<int, int> p : v1_pairs)
    {
	std::cout << p.first << " + " << p.second << " = "
		  << p.first + p.second << std::endl;
    }

    std::cout << "==== Testfall #2 ====" << std::endl;

    
    // Vi vill skriva ut alla par av namn dÃ¤r ena namnet slutar pÃ¥
    // samma bokstav som andra namnet bÃ¶rjar pÃ¥.
    
    // AnvÃ¤nder std::list fÃ¶r att kolla att det fungerar fÃ¶r olika typer
    std::list<std::string> names { "PONTUS", "CHRISTOFFER",
				   "ERIC", "HANNA", "MALTE", "WILHELM" };
    auto name_pairs { get_pairs(names.begin(), names.end()) };

    // Man kan loopa Ã¶ver denna pÃ¥ samma sÃ¤tt som std::map eftersom
    // att den innehÃ¥ller std::pair objekt
    for (auto const& [a, b] : name_pairs)
    {
	// om a slutar pÃ¥ samma bokstav som b bÃ¶rjar pÃ¥...
	if (a.back() == b.front())
	{
	    std::cout << a << " " << b << std::endl;
	}

	// om b slutar pÃ¥ samma bokstav som a bÃ¶rjar pÃ¥...
	else if (a.front() == b.back())
	{
	    std::cout << b << " " << a << std::endl;
	}
    }
}
