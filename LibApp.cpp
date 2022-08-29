/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: LibApp.cpp
Version 2.0
Author	Kevin Timachy
Revision History
-----------------------------------------------------------
Date      Reason
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "LibApp.h"
#include "Menu.h"
#include "Date.h"
#include "PublicationSelector.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
    LibApp::LibApp(const char *file)
    {
        for (int i = 0; i < SDDS_LIBRARY_CAPACITY; i++)
        {
            m_publications[i] = nullptr;
        }

        strcpy(m_dataFile, file);
        load();
        m_changed = false;
        m_mainMenu.setTitle("Seneca Library Application");
        m_mainMenu << "Add New Publication"
                   << "Remove Publication"
                   << "Checkout publication from library"
                   << "Return publication to library";
        m_exitMenu.setTitle("Changes have been made to the data, what would you like to do?");
        m_exitMenu << "Save changes and exit"
                   << "Cancel and go back to the main menu";
        m_pubMenu.setTitle("Choose the type of publication:");
        m_pubMenu
            << "Book"
            << "Publication";
    }
    LibApp::~LibApp()
    {
        for (int i = 0; i < m_noPubLoaded; i++)
        {
            delete m_publications[i];
            m_publications[i] = nullptr;
        }
    }
    bool LibApp::confirm(const char *message)
    {
        Menu confirm(message);
        confirm << "Yes";
        return confirm.run() == 1;
    }
    void LibApp::load()
    {
        cout << "Loading Data" << endl;
        ifstream infile(m_dataFile);
        char type{};
        for (int i = 0; infile && m_noPubLoaded <= SDDS_LIBRARY_CAPACITY; i++)
        {
            infile >> type;
            infile.ignore();
            if (type == 'P')
            {
                m_publications[i] = new Publication;
            }
            else if (type == 'B')
            {
                m_publications[i] = new Book;
            }
            if (m_publications[i] != nullptr)
            {
                infile >> *m_publications[i];
                m_noPubLoaded++;
                if (m_publications[i]->getRef() != -1)
                {
                    m_lastRef = m_publications[i]->getRef();
                }
            }
            type = '\0';
        }
        infile.close();
    }
    void LibApp::save()
    {
        cout << "Saving Data" << endl;
        ofstream outfile(m_dataFile, ofstream::trunc);
        for (int i = 0; i < m_noPubLoaded; i++)
        {
            if (m_publications[i]->getRef() != 0)
            {
                outfile << *m_publications[i];
                outfile << endl;
            }
        }
        outfile.close();
    }
    int LibApp::search(int search)
    {
        char title[SDDS_TITLE_WIDTH] = "\0";
        char type{};
        int ref = 0;
        PublicationSelector ps("Select one of the following found matches:");
        unsigned int selection = m_pubMenu.run();
        if (selection == 1)
            type = 'B';
        else if (selection == 2)
            type = 'P';
        if (selection != 0)
        {
            cout << "Publication Title: ";
            cin.getline(title, SDDS_TITLE_WIDTH, '\n');
            switch (search)
            {
            case 1:
                /* Search all */
                for (int i = 0; i < m_noPubLoaded; i++)
                {
                    if (m_publications[i]->getRef() != 0 && m_publications[i]->type() == type && *m_publications[i] == title)
                        ps << m_publications[i];
                }
                break;
            case 2:
                /* Search loaned */
                for (int i = 0; i < m_noPubLoaded; i++)
                {
                    if (m_publications[i]->getRef() != 0 && m_publications[i]->type() == type && *m_publications[i] == title && m_publications[i]->onLoan())
                        ps << m_publications[i];
                }
                break;
            case 3:
                /* Search available */
                for (int i = 0; i < m_noPubLoaded; i++)
                {
                    if (m_publications[i]->getRef() != 0 && m_publications[i]->type() == type && *m_publications[i] == title && !m_publications[i]->onLoan())
                        ps << m_publications[i];
                }
                break;
            default:
                break;
            }
            if (ps)
            {
                ps.sort();
                ref = ps.run();
                if (!ref)
                {
                    cout << "Aborted!" << endl;
                }
                else
                {
                    cout << *getPub(ref) << endl;
                }
            }
            else
            {
                cout << "No matches found!" << endl;
            }
        }
        else
        {
            cout << "Aborted!" << endl;
        }
        return ref;
    }
    void LibApp::returnPub()
    {
        int daysLate;
        double fee;
        int i;
        cout
            << "Return publication to the library" << endl;
        int ref = search(2);
        if (ref)
        {
            if (confirm("Return Publication?"))
            {
                for (i = 0; i < m_noPubLoaded; i++)
                {
                    if (ref == m_publications[i]->getRef())
                    {
                        daysLate = m_publications[i]->daysOverdue();
                        m_publications[i]->set(0);
                    }
                }
                if (daysLate > 0)
                {
                    fee = daysLate * 0.50;
                    cout << "Please pay $" << fixed << setprecision(2) << fee << " penalty for being " << daysLate << " days late!" << endl;
                }

                m_changed = true;
                cout << "Publication returned" << endl;
            }
        }
    }
    void LibApp::newPublication()
    {
        if (m_noPubLoaded == SDDS_LIBRARY_CAPACITY)
            cout << "Library is at its maximum capacity!" << endl;

        else
        {
            Publication *p = nullptr;
            cout << "Adding new publication to the library" << endl;
            unsigned int selection = m_pubMenu.run();
            if (selection != 0)
            {

                if (selection == 1)
                    p = new Book;
                else if (selection == 2)
                    p = new Publication;
                cin >> *p;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Aborted!" << endl;
                }
                else
                {
                    if (confirm("Add this publication to the library?"))
                    {
                        if (p)
                        {
                            m_lastRef++;
                            p->setRef(this->m_lastRef);
                            m_publications[m_noPubLoaded] = p;
                            m_noPubLoaded++;
                            m_changed = true;
                            cout << "Publication added" << endl;
                        }
                        else
                            cout << "Failed to add publication!" << endl;
                    }
                    else
                        cout << "Aborted!" << endl;
                }
            }
            else
                cout << "Aborted!" << endl;
        }
    }
    void LibApp::removePublication()
    {
        cout << "Removing publication from the library" << endl;
        int ref = search(1);
        if (ref)
        {
            if (confirm("Remove this publication from the library?"))
            {
                for (int i = 0; i < m_noPubLoaded; i++)
                {
                    if (ref == m_publications[i]->getRef())
                    {
                        m_publications[i]->setRef(0);
                    }
                }
                m_changed = true;
                cout << "Publication removed" << endl;
            }
        }
    }
    void LibApp::checkOutPub()
    {
        cout << "Checkout publication from the library" << endl;
        int ref = search(3);
        int id;
        if (ref)
        {
            if (confirm("Check out publication?"))
            {
                cout << "Enter Membership number: ";
                cin >> id;
                while (getMemIDLen(id) != 5)
                {
                    cout << "Invalid membership number, try again: ";
                    cin >> id;
                }
                for (int i = 0; i < m_noPubLoaded; i++)
                {
                    if (ref == m_publications[i]->getRef())
                    {
                        m_publications[i]->set(id);
                        m_publications[i]->resetDate();
                    }
                }
                m_changed = true;
                cout << "Publication checked out" << endl;
            }
        }
    }
    void LibApp::run()
    {
        bool done = false;
        unsigned int selection = 1;
        do
        {
            selection = m_mainMenu.run();
            switch (selection)
            {
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            case 0:
                if (m_changed)
                {
                    selection = m_exitMenu.run();
                    switch (selection)
                    {
                    case 1:
                        save();
                        done = true;
                        break;
                    case 2:
                        break;
                    case 0:
                        if (confirm("This will discard all the changes are you sure?"))
                        {
                            done = true;
                        }
                        break;

                    default:
                        break;
                    }
                }
                else
                {
                    done = true;
                }
            default:
                break;
            }
            cout << endl;
        } while (!done);
        cout << "-------------------------------------------" << endl
             << "Thanks for using Seneca Library Application" << endl;
    }

    Publication *LibApp::getPub(int libRef)
    {
        bool flag = true;
        int i;
        for (i = 0; i < m_noPubLoaded && flag; i++)
        {
            if (libRef == m_publications[i]->getRef())
            {
                flag = false;
            }
        }
        return m_publications[i - 1];
    }

} // namespace sdds