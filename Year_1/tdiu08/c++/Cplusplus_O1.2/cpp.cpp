// Cplusplus_O1.2
// hugho678: Samarbetat med carbj841, Carl Björlin, samma program

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;


int main()
{

  int start, end, longest_size, shortest_size;
  int wordcount {};
  int charcount {};
  int tecken {}, siffra {}, vit {};
  char c;
    
  double kelvin, fahrenheit, reaumur;

  string text, longest_word, shortest_word;
  

  // Del 1: Temperaturtabell

  cout << "Del 1: Temperaturtabell\n";

  do
    {
      cout << "Ange startvärde: ";
      cin >> start;
      if (start < -273)
	{
	  cout << "Felaktigt startvärde!\n";
	}
    }
  while (start < -273);


  do
    {
      cout << "Ange slutvärde: ";
      cin >> end;
      if (end < start)
	{
	cout << "Felaktigt slutvärde!\n";
      }
    }
  while (end < start);
  cin.ignore(1000, '\n');

  cout << "Celsius   Kelvin   Fahrenheit   Reaumur\n";
  cout << setfill('-') << setw(40) << "-\n";

  for (int i = start; i <= end; ++i)
    {
      kelvin = i + 273.15;
      fahrenheit = i * 1.8 + 32;
      reaumur = i * 0.8;

      cout << setfill(' ') << setw(7) << i << setw(9)<< fixed << setprecision(2) << kelvin << setw(13) << fahrenheit << setw(10) << reaumur << '\n';
    }

  cout << setfill('-') << setw(41) << "-\n\n";


  //Del 2: Teckenhantering

  cout << "Del 2: Teckenhantering\n";



  for (int i = 0; i < 10; ++i)
    {
        cin.get(c);
        
        if (isalpha(c))
        {
            tecken++;
        }
        else if (isdigit(c))
        {
            siffra++;
        }
        else if (isspace(c))
        {
            vit++;
        }
    }

  cin.ignore(1000, '\n');

  cout << "Texten innehöll:\n";
  cout << "Alfabetiska tecken:" << tecken << '\n';
  cout << "Siffertecken......:" << siffra << '\n';
  cout << "Vita tecken.......:" << vit << '\n';
  cout <<'\n';


  // Del 3: Ordhantering

  cout << "Del 3: Ordhantering\n" << "Mata in en text:\n";

  while (cin >> text)
    {

        wordcount++;

        if (text.size() > longest_word.size())
        {   
	        longest_word = text;
	        longest_size = text.size();
        }
        if (shortest_word.empty() || text.size() < shortest_word.size())
        {
	        shortest_word = text;
	        shortest_size = text.size();
        }  
        charcount += text.size();
    }

  cin.ignore(1000, '\n');

  cout << '\n';

  if (wordcount == 0)
    {
      cout << "Inga ord matades in.";
    }
  else
    {
      cout << "Texten innehöll " << wordcount << " ord." << endl;
      cout << "Det kortaste ordet var \"" << shortest_word << "\" med " << shortest_size << " tecken." << endl;
      cout << "Det längsta ordet var \"" << longest_word << "\" med " << longest_size << " tecken." << endl;
      cout << "Medelordlängden var " << fixed << setprecision(1) << charcount/(double)wordcount << " tecken.";
    }
  

  return 0;
  
}
