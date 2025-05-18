#include <iostream>

using namespace std;

int main()
{
    int size {};
    char star{'*'};

    while (true)
    {
    cout << "Enter size: ";
    cin >> size;


        if (size < 1)
        {
            cout << "Has to be atleast 1. ";
        }
        else if (size % 2 == 0)
        {
            cout << "Cannot be even. ";
        }
        else if (size > 0)
        {
            break;
        } 
    }

    for (int i {}; i <= size; i++)    
    {
        
        if (i % 2 != 0)
        {
            for (int j {}; j < (-(i-size)/2); j++)
            {
            cout << '.';
            }
            for (int I {}; I < i; I++)
            {
            cout << star;
            }
            for (int j {}; j < (-(i-size)/2); j++)
            {
            cout << '.';
            }
            cout << endl;
        }
        
    }



}
