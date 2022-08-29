/* Citation and Sources...
Final Project Milestone 5
Module: Publication
Filename: Publication.cpp
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
#include "Publication.h"
#include "Date.h"
using namespace std;
namespace sdds
{
    Publication::Publication(const Publication &src)
    {
        m_title = nullptr;
        *this = src;
    }
    Publication::~Publication()
    {
        delete[] m_title;
    }
    Publication &Publication::operator=(const Publication &src)
    {
        if (this != &src)
        {
            m_membership = src.m_membership;
            m_libRef = src.m_libRef;
            m_date = src.m_date;
            strcpy(m_shelfId, src.m_shelfId);
            setTitle(src.m_title);
        }
        return *this;
    }
    void Publication::setTitle(const char *title)
    {
        delete[] m_title;
        if (title != nullptr)
        {
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
        }
        else
            m_title = nullptr;
    }

    void Publication::set(int member_id)
    {
        if (member_id > 9999 && member_id < 100000)
        {
            m_membership = member_id;
        }
        else
            m_membership = 0;
    }
    void Publication::setRef(int value)
    {
        m_libRef = value;
    }
    void Publication::resetDate()
    {
        m_date.setToToday();
    }
    char Publication::type() const
    {
        return 'P';
    }
    bool Publication::onLoan() const
    {
        return m_membership != 0;
    }
    Date Publication::checkoutDate() const
    {
        return m_date;
    }
    bool Publication::operator==(const char *title) const
    {
        return strstr(m_title, title) != nullptr;
    }
    Publication::operator const char *() const
    {
        return m_title;
    }
    int Publication::getRef() const
    {
        return m_libRef;
    }
    int Publication::daysOverdue() const
    {
        return m_date.daysLate();
    }
    bool Publication::conIO(ios &io) const
    {
        return &io == &cin || &io == &cout;
    }
    ostream &Publication::write(ostream &os) const
    {
        char temp[SDDS_TITLE_WIDTH + 1] = "\0";
        if (conIO(os))
        {
            strncpy(temp, m_title, SDDS_TITLE_WIDTH);
            os << "| " << m_shelfId << " | ";
            os.setf(ios::left);
            os.fill('.');
            os.width(30);
            os << temp;
            os << " | ";
            os.unsetf(ios::left);
            if (onLoan())
            {
                os << m_membership << " | ";
            }
            else
            {
                os << " N/A  | ";
            }
            m_date.write(os);
            os << " |";
        }
        else
        {
            os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t";
            m_date.write(os);
        }

        return os;
    }
    istream &Publication::read(istream &istr)
    {
        Publication temp;
        char title[256];

        if (conIO(istr))
        {
            cout << "Shelf No: ";
            istr.getline(temp.m_shelfId, (SDDS_SHELF_ID_LEN + 1));
            if (strlen(temp.m_shelfId) != SDDS_SHELF_ID_LEN)
            {
                istr.setstate(ios::failbit);
            }
            cout << "Title: ";
            istr.getline(title, (265));
            temp.setTitle(title);
            cout << "Date: ";
            istr >> temp.m_date;
        }
        else
        {
            istr >> temp.m_libRef;
            istr.ignore(100, '\t');
            istr.getline(temp.m_shelfId, (SDDS_SHELF_ID_LEN + 1), '\t');
            istr.getline(title, (256), '\t');
            temp.setTitle(title);
            istr >> temp.m_membership;
            istr >> temp.m_date;
        }
        if (!temp.m_date)
        {
            istr.setstate(ios::failbit);
        }
        if (!istr.fail())
        {
            *this = temp;
        }

        return istr;
    }

    Publication::operator bool() const
    {
        return m_title && m_title[0] != '\0' && m_shelfId[0] != '\0';
    }

} // namespace sdds
