#ifndef RUNNER_H
#define RUNNER_H

#include <string>
#include <vector>

struct Runner {
    std::string firstName {""};
    std::string lastName {""};
    std::string club {""};
    std::vector<double> times;
};

Runner inputRunner();
void print(Runner const& r);

bool operator<(Runner const& left,
               Runner const& right);


#endif