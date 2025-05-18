// Cplusplus_O3
// hugho678: Samarbetat med carbj841, Carl Björlin, samma program

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include "runner_handling.h"


using namespace std;

using runner_vector_type = vector<runner_type>;
using time_vector_type = vector<double>;


int main()
{
runner_vector_type runners;
time_vector_type times;

runner_type runner;
//string klar;
//int loop {};

string user_input;
double user_double;
//int user_double;

cout << "Mata in deltagare:\n";
while (1)
{        
    cin >> user_input;
    if (user_input == "KLAR") 
    {
        break;
    }
    else
    {
        runner.first_name = user_input;
        cin >> runner.last_name >> runner.club >> runner.club_short;
        runners.push_back(runner);
    }
}

    for (int i = 0; i < runners.size(); i++)
    {

    get_times(runners.at(i), times);
      

    //sort(begin(times), end(times));

    }
       // sort(begin(times), end(times));
    //sort(begin(runners), end(runners));

    cout << "Efternamn" << setw(11) << "Förnamn" << setw(23) << "Klubb: Tider\n";
    cout << setfill('=') << setw(43) << '\n';
    for (int i = 0; i < runners.size(); i++)
    {
        print_runner(runners.at(i));
        for (int i = 0; i < times.size(); i++)
        {
        cout << fixed << setprecision(2) << times.at(i);
        }
    }


    return 0;
}