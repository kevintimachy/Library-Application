/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    // MENUITEM
    MenuItem::MenuItem()
    {
        m_content = nullptr;
    }
    MenuItem::MenuItem(const char *content)
    {
        setContent(content);
    }
    MenuItem::~MenuItem()
    {
        delete[] m_content;
    }
    void MenuItem::setContent(const char *content)
    {
        if (content && content[0] != '\0')
        {
            m_content = new char[strlen(content) + 1];
            strcpy(m_content, content);
        }
        else
            m_content = nullptr;
    }
    MenuItem::operator bool() const
    {
        return m_content != nullptr && m_content[0] != '\0';
    }
    MenuItem::operator const char *()
    {
        return m_content;
    }
    ostream &MenuItem::display(ostream &os) const
    {
        if (m_content != nullptr)
        {
            os << m_content;
        }
        return os;
    }

    // MENU
    Menu::Menu() : m_ptr{0}
    {
    }
    Menu::Menu(const char *title) : m_title(title), m_ptr{0}
    {
    }
    Menu::~Menu()
    {
        for (unsigned int i = 0; i < m_ptr; i++)
        {
            delete m_items[i];
            m_items[i] = nullptr;
        }
    }
    void Menu::setTitle(const char *title)
    {
        m_title.setContent(title);
    }
    ostream &Menu::displayTitle(ostream &os) const
    {
        if (m_title)
            m_title.display(os);
        return os;
    }
    ostream &Menu::display(ostream &os) const
    {
        if (*this)
        {
            if (m_title)
            {
                displayTitle(os);
                os << endl;
            }
            for (unsigned int i = 0; i < m_ptr; i++)
            {
                os << " " << i + 1 << "- ";
                m_items[i]->display(os);
                os << endl;
            }
            os << " 0- Exit" << endl;
            os << "> ";
        }
        return os;
    }
    unsigned int Menu::run() const
    {
        display(cout);
        unsigned int selection = (unsigned int)getIntInRange("Invalid Selection, try again: ", 0, m_ptr);
        return selection;
    }
    unsigned int Menu::operator~() const
    {
        return run();
    }

    Menu &Menu::operator<<(const char *menuitemConent)
    {
        if (m_ptr < MAX_MENU_ITEMS)
        {
            m_items[m_ptr] = new MenuItem(menuitemConent);
            m_ptr++;
        }
        return *this;
    }
    Menu::operator unsigned int() const
    {
        return m_ptr;
    }
    Menu::operator int() const
    {
        return (int)m_ptr;
    }
    Menu::operator bool() const
    {
        return m_ptr > 0;
    }
    const char *Menu::operator[](int position) const
    {
        int index = position;
        if (position >= (int)m_ptr)
        {
            index = position % m_ptr;
        }
        return m_items[index]->m_content;
    }
    ostream &operator<<(ostream &os, const Menu &m)
    {
        return m.displayTitle(os);
    }
}