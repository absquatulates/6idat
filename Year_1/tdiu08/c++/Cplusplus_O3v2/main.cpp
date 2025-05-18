#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

#include "runner.h"
#include "runnerlist.h"

using namespace std;


int main ()
{
    Runner runner;
    runnerlist_vector runnerlist;
    
    
    cout << "Mata in deltagare:" << endl;

    while (true)
    {
    runner = inputRunner();
        if (runner.firstName == "KLAR")
        {
            break;
        }
        runnerlist.push_back(runner);
    }

    inputTimes(runnerlist);

    sort(begin(runnerlist), end(runnerlist));
    printRunners(runnerlist);

    return 0;

}