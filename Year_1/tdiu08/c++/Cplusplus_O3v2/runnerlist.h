#ifndef RUNNERLIST_H
#define RUNNERLIST_H

#include <string>
#include <vector>
#include "runner.h"

using runnerlist_vector = std::vector<Runner>;
void printRunners (runnerlist_vector const& list);
void inputTimes(runnerlist_vector & runnerlist);

#endif