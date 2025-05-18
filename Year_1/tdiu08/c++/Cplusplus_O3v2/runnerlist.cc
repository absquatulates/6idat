#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

#include "runner.h"
#include "runnerlist.h"

using namespace std;

void printRunners(runnerlist_vector const& list)
{

    cout << "Efternamn" << setw(11) << "Förnamn" << setw(24) << "Klubb: Tider\n";
    cout << setfill('=') << setw(43) << '\n';

    for (int i {}; i < list.size(); i++)
    {
        print(list.at(i));
    }

}



void inputTimes(runnerlist_vector & runnerlist)
{
    double time {};
    
for (int i {}; i < runnerlist.size(); i++)
    {
        cout << "Tider " << runnerlist.at(i).firstName << ": ";
        while (true)
        {
        cin >> time;
            if (time == -1.00)
            {
                break;
            }
            runnerlist.at(i).times.push_back(time);
        }
        sort(begin(runnerlist.at(i).times), end(runnerlist.at(i).times));
    }
}
