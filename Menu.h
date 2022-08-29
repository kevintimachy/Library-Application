/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.h
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
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
namespace sdds
{
    const unsigned int MAX_MENU_ITEMS = 20;
    class Menu;
    class MenuItem
    {
    private:
        friend class Menu;
        char *m_content;

        MenuItem();
        MenuItem(const char *content);
        MenuItem(const MenuItem &src) = delete;
        ~MenuItem();
        void setContent(const char *content);
        MenuItem &
        operator=(const MenuItem &src) = delete;
        operator bool() const;
        operator const char *();
        std::ostream &display(std ::ostream &os = std::cout) const;
    };
    class Menu
    {
    private:
        MenuItem m_title;
        MenuItem *m_items[MAX_MENU_ITEMS];
        unsigned int m_ptr;

    public:
        Menu();
        Menu(const char *title);
        Menu(const Menu &src) = delete;
        ~Menu();
        void setTitle(const char *title);
        Menu &operator=(const Menu &src) = delete;
        std::ostream &displayTitle(std::ostream &os) const;
        std::ostream &display(std::ostream &os) const;
        unsigned int run() const;
        unsigned int operator~() const;
        Menu &operator<<(const char *menuitemConent);
        operator unsigned int() const;
        operator int() const;
        operator bool() const;
        const char *operator[](int position) const;
    };
    std::ostream &operator<<(std::ostream &os, const Menu &m);
}

#endif