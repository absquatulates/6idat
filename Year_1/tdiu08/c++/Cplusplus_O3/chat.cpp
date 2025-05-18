#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Post-datatyp för en löpare
struct Runner {
    std::string firstName;
    std::string lastName;
    std::string club;
    std::string clubs;
    std::vector<double> times; // Vektor för att lagra löparens tider

    // Funktion för att beräkna och returnera löparens snabbaste tid
    double getFastestTime() const {
        if (times.empty()) {
            return -1.0;
        }
        return *std::min_element(times.begin(), times.end());
    }
};

// Funktion för att mata in löpare
Runner inputRunner() {
    Runner runner;
    std::cin >> runner.firstName;
    if (runner.firstName != "KLAR") {
        std::cin >> runner.lastName >> runner.club >> runner.clubs;
    }

    return runner;
}

// Funktion för att mata in tider för en löpare
void inputTimes(Runner &runner) {
    double time;
       
       /*
        while (true)
            {
            if (user_double == -1.00)
            {
                break;
            }
            else
            {
            cin >> user_double;
            time = user_double;
            }
        }
        */
    
    
    while (std::cin >> time && time != -1.00) 
    {
       runner.times.push_back(time);
    }
    }


// Funktion för att skriva ut en löpare
void printRunner(const Runner &runner) {
    std::cout << runner.lastName << " " << runner.firstName << " " << runner.club << ": ";
    for (const auto &time : runner.times) {
        std::cout << time << " ";
    }
    std::cout << std::endl;
}

using runner_vector = vector<Runner>;

int main() {
    runner_vector runners;
    Runner runner;

    // Mata in löpare
    std::cout << "Mata in deltagare: \n";
    while (true) 
    {
        Runner runner =  inputRunner();
        if (runner.firstName == "KLAR") 
        {
            break;
        }
        runners.push_back(runner);
    }
    for (int i = 0; i < runners.size();)
    {
    inputTimes(runners.at(i));
    std::cout << "Tider " << runners.at(i).firstName << ": ";
    }
   
    

    // Sortera löpare efter snabbaste tid
    std::sort(runners.begin(), runners.end(),
              [](const Runner &a, const Runner &b) {
                  return a.getFastestTime() < b.getFastestTime();
              });

    // Skriv ut resultatet
    std::cout << "\nEfternamn Förnamn Klubb: Tider\n";
    std::cout << "==========================================\n";
    for (const auto &runner : runners) {
        printRunner(runner);
    }

    return 0;
}