/* Citation and Sources...
Final Project Milestone 5
Module: Streamable
Filename: Streamable.h
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
#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include <iostream>

namespace sdds
{
    class Streamable
    {
    private:
        /* data */
    public:
        virtual std::ostream &write(std::ostream &) const = 0;
        virtual std::istream &read(std::istream &) = 0;
        virtual bool conIO(std::ios &) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable() = default;
    }; // namespace sdds

    std::istream &operator>>(std::istream &, Streamable &);
    std::ostream &operator<<(std::ostream &, const Streamable &);
}
#endif