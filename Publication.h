/* Citation and Sources...
Final Project Milestone 5
Module: Publication
Filename: Publication.h
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
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include "Date.h"
#include "Streamable.h"
#include "Lib.h"

namespace sdds
{
    class Publication : public Streamable
    {
    private:
        char *m_title = nullptr;
        char m_shelfId[SDDS_SHELF_ID_LEN + 1] = {'\0'};
        int m_membership = 0;
        int m_libRef = -1;
        Date m_date = Date();

    public:
        Publication() = default;
        Publication(const Publication &);
        ~Publication();
        Publication &operator=(const Publication &);
        virtual void set(int member_id);
        // Sets the membership attribute to either zero or a five-digit integer.
        void setRef(int value);
        // Sets the **libRef** attribute value
        void resetDate();
        // Sets the date to the current date of the system.
        void setTitle(const char *);
        // Sets the title
        virtual char type() const;
        //Returns the character 'P' to identify this object as a "Publication object"
        bool onLoan() const;
        //Returns true is the publication is checkout (membership is non-zero)
        Date checkoutDate() const;
        //Returns the date attribute
        bool operator==(const char *title) const;
        //Returns true if the argument title appears anywhere in the title of the
        //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
        operator const char *() const;
        //Returns the title attribute
        int getRef() const;
        //Returns the libRef attirbute.
        int daysOverdue() const;
        bool conIO(std::ios &io) const;
        //Returns true if the address of the io object is the same as the address of either the cin object or the cout object.
        virtual std::ostream &write(std::ostream &os) const;
        //If the os argument is a console IO object (use conIO()), print shelfId, title, membership and date attributes as the following format (title is left-justified padded with dots)
        virtual std::istream &read(std::istream &istr);
        //Read all the values in local variables before setting the attributes to any values.
        virtual operator bool() const;
        //Returns true if neither of the title or shelfId attributes is null or empty. Otherwise, it will return false.
    };

} // namespace sdds

#endif