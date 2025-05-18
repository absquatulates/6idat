#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

using double_vector = vector<double>;

struct Runner 
{
    string         firstName;
    string         lastName;
    string         club;
    string         clubShort;
    double_vector  times;
};

Runner getRunner(Runner runner)
{

    cin >> runner.firstName;
    if (runner.firstName != "KLAR")
    {
        //runner.firstName = user_data;
        cin >> runner.lastName >> runner.club >> runner.clubShort;
    }

    return runner;   
}

void getTimes(Runner runner)
{
    double time;

    cout << "Tider " << runner.firstName << ": ";
    while (cin >> time)
    {
        if (time != -1.00)
        {
            runner.times.push_back(time);          
        }
        else
        {
            break;
        }
    }
}

void printRunners(Runner const runner)
{
    cout << runner.firstName << ' ' << runner.lastName << ' ' << runner.club << ' ' << runner.clubShort << endl;
    for (int i = 0; i < runner.times.size(); i++)
    {
    cout << time << ' ';
    }
}




int main()
{
    Runner runner;
    vector<Runner> runners {};

    cout << "Mata in en deltagare:" << endl;
    while (true)
    {
        runner = getRunner(runner);
        if (runner.firstName == "KLAR")
        {
            break;
        }
        runners.push_back(runner);

    }


    for (int i = 0; i < runners.size(); i++)
    {
        //cout << runners.at(i).firstName;
        getTimes(runners.at(i));
    }

    //sort(begin(runners), end(runners));

    for (int i = 0; i < runners.size(); i++)
    {
    printRunners(runners.at(i));
   // cout runners.times.at(i);
    }
    cout << runners.at(0).times.at(0);
    //cout << '\n' << runners.at(0).firstName << '\n' << runners.at(1).firstName;
    //sort(begin(runner.times), end(runner.times));

    return 0;
}