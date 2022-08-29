/* Citation and Sources...
Final Project Milestone 5
Module: Book
Filename: Book.h
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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <iostream>
#include "Publication.h"

namespace sdds
{
    class Book : public Publication
    {
    private:
        char *m_authorName = nullptr;

    public:
        Book() = default;
        Book(const Book &src);
        ~Book();
        Book &operator=(const Book &src);
        virtual void set(int member_id);
        void setAuthor(const char *author);
        virtual std::ostream &write(std::ostream &os) const;
        virtual std::istream &read(std::istream &istr);
        virtual operator bool() const;
        virtual char type() const;
    };

} // namespace sdds

#endif