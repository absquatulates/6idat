#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

#include "runner.h"

using namespace std;

Runner inputRunner()
{
    Runner runner;
    
    cin >> runner.firstName;
    if (runner.firstName != "KLAR")
    {
        cin >> runner.lastName;
        getline(cin, runner.club);
    }

    return runner; 
}
bool operator<(Runner const& left,
               Runner const& right)
{
    return left.times.at(0) < right.times.at(0);
} 

void print(Runner const& r)
{
    cout << setfill(' ') << right << setw(9) << r.lastName << setw(10) << r.firstName << setw(16) << r.club << ": ";
    for (int i {}; i < r.times.size(); i++)
    {
        cout << fixed << setprecision(2) << r.times.at(i);
        if (i < r.times.size() - 1)
        {   
            cout << ' ';
        }
    }
    cout << endl;
}
