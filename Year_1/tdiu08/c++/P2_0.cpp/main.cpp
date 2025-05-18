#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;


void printColumns1(int const columns,
                  int const size)
{
        for (int i {}; i < columns/2; i++)
    {
        for (int i {}; i < size*2; i++)
        {
            cout << '#';
        }
        for (int i {}; i < size*2; i++)
        {
            cout << '.';
        }
    }  
}

void printColumns2(int const columns,
                  int const size)
{
        for (int i {}; i < columns/2; i++)
    {
        for (int i {}; i < size*2; i++)
        {
            cout << '.';
        }
        for (int i {}; i < size*2; i++)
        {
            cout << '#';
        }
    }  
}


void chess(int const columns,
           int const rows,
           int const size)
{
    for (int i {}; i < rows/2; i++)
    {
        for (int i {}; i < size; i++)
        {
        printColumns1(columns, size);
        cout << endl;
        }
        if (rows > 1)
        {
            for (int i {}; i < size; i++)
            {
            printColumns2(columns, size);
            cout << endl;
            }
        }
    }
    
}


int main()
{
    int columns {};
    int rows {};
    int size {};

    cout << "Enter number of columns, rows and size: ";
    cin >> columns >> rows >> size;

    chess(columns, rows, size);


    return 0;
}