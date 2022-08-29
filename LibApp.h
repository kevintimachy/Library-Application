/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: LibApp.h
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
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <iostream>
#include "Menu.h"
#include "Publication.h"
#include "Book.h"

namespace sdds
{
    class LibApp
    {
    private:
        char m_dataFile[256];
        Publication *m_publications[SDDS_LIBRARY_CAPACITY];
        int m_noPubLoaded = 0;
        int m_lastRef = 0;
        Menu m_pubMenu;
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;

        bool confirm(const char *message);
        void load();                // prints: "Loading Data"<NEWLINE>
        void save();                // prints: "Saving Data"<NEWLINE>
        int search(int search = 1); // prints: "Searching for publication"<NEWLINE>

        void returnPub(); /*  Calls the search() method.
                              prints "Returning publication"<NEWLINE>
                              prints "Publication returned"<NEWLINE>
                              sets m_changed to true;
                          */
        void newPublication();
        void removePublication();
        void checkOutPub();
        Publication *getPub(int libRef);

    public:
        LibApp(const char *file);
        ~LibApp();

        void run();
    };

} // namespace sdds

#endif