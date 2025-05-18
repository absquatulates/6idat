#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <numeric>
#include <cctype>

int main()
{   
    // 1 & 2
    std::vector<std::string> data { std::istream_iterator<std::string>{std::cin},
                                    std::istream_iterator<std::string>{} };

    // 3. (En av dessa slumpas ut)
    
    // Ta bort alla ord som börjar med stor bokstav. Tips: \lstinline|std::isupper| kan vara användbar.
    data.erase(std::remove_if(data.begin(), data.end(), [](std::string const& word)
                                                        {
                                                            return std::isupper(word.front());
                                                        }), data.end());

    // Ta bort alla ord som är kortare än 3 tecken.
    data.erase(std::remove_if(data.begin(), data.end(), [](std::string const& word)
                                                        {
                                                            return word.size() <= 3;
                                                        }), data.end());

    // Ta bort alla ord som börjar och slutar på samma tecken.
    data.erase(std::remove_if(data.begin(), data.end(), [](std::string const& word)
                                                        {
                                                            return word.front() == word.back();
                                                        }), data.end());

    // Ta bort alla ord vars längd är udda.
    data.erase(std::remove_if(data.begin(), data.end(), [](std::string const& word)
                                                        {
                                                            return word.size() % 2 == 1;
                                                        }), data.end());

    // Ta bort alla ord som \emph{inte} slutar på en bokstav. Tips: \lstinline|std::isalpha| kan vara användbar.
    data.erase(std::remove_if(data.begin(), data.end(), [](std::string const& word)
                                                        {
                                                            return !std::isalpha(word.back());
                                                        }), data.end());

    // Ta bort alla ord som börjar med 'a' eller 'A'.
    data.erase(std::remove_if(data.begin(), data.end(), [](std::string const& word)
                                                        {
                                                            return word.front() == 'a' || word.front() == 'A';
                                                        }), data.end());
    

    // 4.

    // Om alla ord togs bort i förra steget, avsluta då programmet med ett lämpligt meddelande.
    if (data.empty())
    {
        std::cout << "Inga ord kvar." << std::endl;
        return 0;
    }

    // 5.

    // Räkna ut summan av ordens längd som en \lstinline|double| och dela sedan
    // med antalet ord för att få genomsnittliga längden.
    double avg { std::accumulate(data.begin(), data.end(), 0,
                              [](int n, std::string const& word)
                              {
                                  return n + word.size();
                              }) };
    avg = avg / data.size();

    // 6. (En av dessa slumpas ut)

    // Dela listan i två delar, med alla tal som är kortare än
    // genomsnittet till vänster och de som är större till höger.

    std::partition(data.begin(), data.end(), [avg](std::string const& word)
                                             {
                                                 return word.size() < avg;
                                             });

    // Ersätt alla ord som är kortare än genomsnittet med det första
    // ordet i listan.
    std::replace_if(data.begin(), data.end(), [avg](std::string const& word)
                                              {
                                                  return word.size() < avg;
                                              }, data.front());

    // Skriv ut antalet ord som är längre än genomsnittet.
    std::cout << "Antal ord som är längre än genomsnittet: "
              << std::count_if(data.begin(), data.end(), [avg](std::string const& word)
                                                         {
                                                             return word.size() > avg;
                                                         }) << std::endl;

    // Skriv ut det första ordet som är mindre eller lika med genomsnittet.
    std::cout << "Första ordet som är mindre eller lika med genomsnittet: "
              << *std::find_if(data.begin(), data.end(), [avg](std::string const& word)
                                                         {
                                                             return word.size() <= avg;
                                                         }) << std::endl;

    // Lägg till tecknet '*' i slutet av alla ord som är lika långa som genomsnittet.
    std::transform(data.begin(), data.end(), data.begin(), [avg](std::string const& word)
                                                           {
                                                               if (word.size() == avg)
                                                               {
                                                                   return word + '*';
                                                               }
                                                               return word;
                                                           });

    // 7. (En av dessa slumpas ut)

    // Sortera orden i stigande ordning med avseende på längden.
    std::sort(data.begin(), data.end(), [](std::string const& a,
                                           std::string const& b)
                                        {
                                            return a.size() < b.size();
                                        });

    // Sortera orden i fallande ordning, d.v.s. från Z till A.
    std::sort(data.begin(), data.end(), [](std::string const& a,
                                           std::string const& b)
                                        {
                                            return a > b;
                                        });

    // Sortera orden i stigande ordning med avseende på det första tecknet i varje ord.
    std::sort(data.begin(), data.end(), [](std::string const& a,
                                           std::string const& b)
                                        {
                                            return a.back() < b.back();
                                        });

    // 8. Skriv ut listan, med varje ord på egen rad.

    std::copy(data.begin(), data.end(), std::ostream_iterator<std::string>{std::cout, "\n"});
    
}
