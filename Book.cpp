/* Citation and Sources...
Final Project Milestone 5
Module: Book
Filename: Book.cpp
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
#include <cstring>
#include "Book.h"
using namespace std;

namespace sdds
{
    Book::Book(const Book &src)
    {
        *this = src;
    }
    Book::~Book()
    {
        delete[] m_authorName;
    }
    Book &Book::operator=(const Book &src)
    {
        if (this != &src)
        {
            setAuthor(src.m_authorName);
            Publication::operator=(src);
        }
        return *this;
    }
    char Book::type() const
    {
        return 'B';
    }
    ostream &Book::write(ostream &os) const
    {
        char temp[SDDS_AUTHOR_WIDTH + 1] = "\0";
        Publication::write(os);
        if (conIO(os))
        {
            strncpy(temp, m_authorName, SDDS_AUTHOR_WIDTH);
            os << " ";
            os.setf(ios::left);
            os.width(SDDS_AUTHOR_WIDTH);
            os.fill(' ');
            os << temp;
            os << " |";
        }
        else
        {
            os << "\t" << m_authorName;
        }

        return os;
    }
    istream &Book::read(istream &istr)
    {
        char author[256] = "\0";
        Publication::read(istr);
        if (conIO(istr))
        {
            istr.ignore(1, '\n');
            cout << "Author: ";
            istr.getline(author, 256);
        }
        else
        {
            istr.ignore(1, '\t');
            istr.getline(author, 256);
            istr.seekg(-1, ios_base::cur);
        }
        if (istr)
        {
            setAuthor(author);
        }

        return istr;
    }
    void Book::setAuthor(const char *author)
    {
        delete[] m_authorName;
        if (author != nullptr)
        {
            m_authorName = new char[strlen(author) + 1];
            strcpy(m_authorName, author);
        }
        else
            m_authorName = nullptr;
    }
    void Book::set(int member_id)
    {
        Publication::set(member_id);
        Publication::resetDate();
    }
    Book::operator bool() const
    {
        return m_authorName && m_authorName[0] != '\0';
    }
} // namespace sdds
