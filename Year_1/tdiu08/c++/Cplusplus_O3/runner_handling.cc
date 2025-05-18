#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


#include "runner_handling.h"

using namespace std;

void get_times(runner_type & runner, 
               vector<double> & times)
{
    double user_double;
    //time_vector_type times;


    cout << "Tider " << runner.first_name << ": ";
            while (1)
        {
            if (user_double == -1.00)
            {
                break;
            }
            else
            {
            cin >> user_double;
            runner.time = user_double;
            times.push_back(runner.time);
            }
        }

}

void print_runner(runner_type const & runner)
{
    

       cout << setfill(' ') << runner.last_name << left << setw(11) << runner.first_name << ' ' << runner.club << ' ' << runner.club_short;
    
}