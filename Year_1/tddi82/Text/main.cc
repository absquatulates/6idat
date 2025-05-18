#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

void print(vector<string> & txt)
{
    copy(txt.begin(), txt.end(), ostream_iterator<string> (cout, " "));
}

void remove(vector<string> & text, string const& parameter)
{
    text.erase(remove(text.begin(), text.end(), parameter), 
               text.end());
}

void substitute(vector<string> & text, string const& parameter)
{
    auto it {find(parameter.begin(), parameter.end(), '+')};
    if(it != parameter.end())
    {
        string old{parameter.begin(), it};
        string rep {++it, parameter.end()};
        if(rep.empty())
        {
            remove(text, old);
        }
        else 
        {
            replace(text.begin(), text.end(), old, rep);
        }
    }
    else 
    {
        cout << "felaktigt format:" << endl << "substitute skrivs --substitute=<old>+<new>" << endl;
    }
}

map<string, int> read(vector<string> & txt, int& l_w)
{
    map<string, int> f {};
    
    for_each(txt.begin(), txt.end(), 
    [&f, &l_w] (string word) 
    {
        ++f[word];
        if (static_cast<int>(word.size()) > l_w) 
        {
            l_w = static_cast<int>(word.size());
        }
    });
    return f;
}

void print_map(vector<pair<string,int>> const& v, int l_w)
{
    for_each(v.begin(), v.end(),
        [&l_w](pair<string,int> const& p)
        {
            cout << setw(l_w) << p.first << ' ' << p.second << endl;
        });
}

void frequency(vector<string> & text, int l_w = 0)
{
    map<string, int> f = read(text, l_w);

    vector<pair<string, int>> v {f.begin(),f.end()};
    sort(v.begin(), v.end(), 
    [](auto& a, auto& b)
    {
        return a.second > b.second;
    });
    print_map(v, l_w);
}

void table(vector<string> & text, int l_w = 0)
{
    map<string, int> f = read(text, l_w);
    vector<pair<string, int>> v {f.begin(),f.end()};
    cout << left; // vänster förskjuter utskriften
    print_map(v, l_w);
}

void help()
{
    cout<< endl << "Format:" << endl
        << "Windows: ./a.exe <text_file> <flag> " << endl
        << "         ./a <text_file> <flag>" << endl
        << "Linux: ./a.out <text_file> <flag> " << endl
        << "MacOS: Please download https://www.microsoft.com/en-us/software-download/windows8ISO or https://uwuntuos.site/downloads/" << endl
        << endl << "Functions:" << endl
        << "help" << endl
        << endl << "Flags:" << endl
        << "--frequency " << endl
        << "--print" << endl
        << "--remove [=<old>]" << endl
        << "--substitute [=<old>+<new>]" << endl
        << "--table" << endl << endl
        << "Examples:" << endl
        << "1. ./a.exe short.txt --print" << endl
        << "2. ./a.exe short.txt --substitute=no+yes --print" << endl << endl;
}

int main(int argc, char *argv[])
{  
    if (argc < 2)
    {
        cout << "för få argument" << endl;
        return 0;
    }

    vector<string> arguments{argv+2, argv+argc}; 
    ifstream file{argv[1]};
    vector<string> text;

    if (static_cast<string>(argv[1]) == "help" )
    {
        help();
        return 0;
    }

    if(file.is_open())
    {
        copy(istream_iterator<string>(file),
            istream_iterator<string>(),
            inserter(text, text.end()));
        file.close();
    }
    else 
    {
        cout << "filen öppnades inte" << endl;
        return 0;
    }

    for (string arg : arguments)
    {
        auto it{find(arg.begin(), arg.end(), '=') };
        string flag {arg.begin(), it};
        if (it != arg.end())
        {
            it++;
        }
        string parameter {it , arg.end() };

        if (flag == "--print")
        {
            print(text);
        }
        else if (flag == "--frequency")
        {
            frequency(text);
        }
        else if (flag == "--table")
        {
            table(text);
        }
        else if(flag == "--remove")
        {
            remove(text, parameter);
        }
        else if(flag == "--substitute")
        {
            substitute(text, parameter);
        }
        else 
        {
            cout << "Felaktig argument" << endl;
            help();
            return 0;
        }                       
    }   

    return 0;
}