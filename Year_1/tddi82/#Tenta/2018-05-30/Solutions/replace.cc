#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

string wordtolower(string s)
{
  transform(begin(s), end(s), begin(s), ::tolower);
  return s;
}

int main()
{
  ifstream file{"given_files/SUBSTITUTIONS.TXT"};

  map<string,string> dict;
  string search;
  string replace;
  while ( getline( getline( file, search, ':'), replace) )
  {
    dict[ wordtolower(search) ] = wordtolower(replace);
  }
  map<string,string> const& cdict{dict};
  
  transform( istream_iterator<string>{cin}, istream_iterator<string>{},
             ostream_iterator<string>{cout, " "},
             [&cdict](string s){
               string l{wordtolower(s)};
               if ( cdict.count(l) )
                 return cdict.at(l);
               else
                 return s;
             });

  cout << endl;
  return 0;
}
