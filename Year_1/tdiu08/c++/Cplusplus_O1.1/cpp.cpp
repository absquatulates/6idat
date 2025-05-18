// Cplusplus_O1.1
// hugho678: Samarbetat med carbj841, Carl Björlin, samma program


// Behöver fler cin.ignore
// Rätt lösning finns i thinlink

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


int main()
{
    
    int I;
    double F;
    char C;
    string S;


    cout << "Skriv in ett heltal: ";
    cin >> I;
    cout << "Du skrev in heltalet:" << setw(2) << I << "\n\n";


    cout << "Skriv in fem heltal: ";
    cin >> I;
    cout << "Du skrev in heltalen: ";

    for (int i {}; i < 4; ++i)
    {
    cout << I << ' ';
    cin >> I;
    }
    cout << I << "\n\n";


    cout << "Skriv in ett flyttal: ";
    cin >> F;
    cout << "Du skrev in flyttalet: " << fixed << setprecision(3) << F << "\n\n";


    cout << "Skriv in ett heltal och ett flyttal: ";
    cin >> I >> F;
    cout << "Du skrev in heltalet:" << setw(10) << I << endl;
    cout << "Du skrev in flyttalet:" << fixed << setprecision(4) << setw(10) << F << "\n\n";


    cout << "Skriv in ett flyttal och ett heltal: ";
    cin >> F >> I;
    cout << "Du skrev in heltalet:" << setfill('-') << setw(10) << I << endl;
    cout << "Du skrev in flyttalet:" << fixed << setprecision(4) << setfill('-') << setw(10) << F << "\n\n";

    cout << "Skriv in ett tecken: ";
    cin >> C;
    cout << "Du skrev in tecknet: " << C << "\n\n";


    cout << "Skriv in ett ord: ";
    cin >> S;
    cout << "Du skrev in ordet: " << S << "\n\n"; 


    cout << "Skriv in ett heltal och ett ord: ";
    cin >> I >> S;
    cout << "Du skrev in heltalet |" << I << "| och ordet |" << S << "|. \n\n";


    cout << "Skriv in ett tecken och ett ord: ";
    cin >> C >> S;
    cout << "Du skrev in " << '"' << S <<'"' << " och " << '"' << C << '"' << ".\n\n";


    cout << "Skriv in ett ord och ett tecken: ";
    cin >> S >> C;
    cin.ignore(1000, '\n');
    cout << "Du skrev in " << '"' << S <<'"' << " och " << '"' << C << '"' << ".\n\n";


    cout << "Skriv in en textrad: ";
    getline(cin, S);
    cout << "Du skrev in " << '"' << S << '"' <<".\n\n";


    cout << "Skriv in en till rad text: ";
    getline(cin, S);
    cout << "Du skrev in " << '"' << S << '"'<< ".\n\n";


    cout << "Skriv in en rad med tre ord: ";
    cin >> S;
    cout << "Du skrev in: " << '"' << S << '"' << ", ";
    cin >> S;
    cout << '"' << S << '"' << " och " << '"';
    cin >> S;
    cout << S <<'"' << '.';

    return 0;
}