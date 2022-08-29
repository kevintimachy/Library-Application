/* Citation and Sources...
Final Project Milestone 5
Module: Streamable
Filename: Streamable.cpp
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
#include "Streamable.h"
using namespace std;

namespace sdds
{
    istream &operator>>(istream &is, Streamable &stream)
    {
        stream.read(is);
        return is;
    }
    ostream &operator<<(ostream &os, const Streamable &stream)
    {
        if (stream)
        {
            stream.write(os);
        }
        return os;
    }
} // namespace sdds
