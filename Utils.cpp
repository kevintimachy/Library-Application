/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: Utils.cpp
Version 1.0
Author	Kevin Timachy
Revision History
-----------------------------------------------------------
Date      Reason
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
-----------------------------------------------------------*/
#include <iostream>
using namespace std;
#include "Utils.h"
namespace sdds
{
    int getIntInRange(const char *error, int lowerbound, int upperbound)
    {
        int x;
        cin >> x;
        while (cin.fail() || x < lowerbound || x > upperbound)
        {
            cout << error;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> x;
        }
        cin.clear();
        cin.ignore(256, '\n');
        return x;
    }

    int getMemIDLen(int id)
    {
        int count = 0;
        while (id != 0)
        {
            id = id / 10;
            count++;
        }
        return count;
    }
}