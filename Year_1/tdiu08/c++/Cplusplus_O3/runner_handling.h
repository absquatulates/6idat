#ifndef RUNNER_HANDLING_H
#define RUNNER_HANDLING_H

#include <string>
#include <vector>


struct runner_type
{
    std::string first_name;
    std::string last_name;
    std::string club;
    std::string club_short;
    vector<double> time;
};


void get_times(runner_type & runner, vector<double> & times);
void print_runner(runner_type const& runner);



#endif
