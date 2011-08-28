
#include "MenuJoin.h"

#include <map>
#include <string>

#include "util/globals.h"
#include "network/NetworkManager.h"

MenuJoin::MenuJoin(Menu *parent) :
        Menu(parent)
{
    gNetwork->initClient();
    m_menu_actions.add_action_string("IP", 1, "192.168.1.1");
    m_menu_actions.add_action_classic("Refresh", 2);
    m_menu_actions.add_action_classic("Return", 3);
    m_size = 0;
}

MenuJoin::~MenuJoin()
{

}

void MenuJoin::treat_choice(int choice)
{
    if ( choice == 1 ) { //join
        //
    } else if ( choice == 2 ) { //refresh
        //Pas trop utile avec une frequence de 5s...
    } else if ( choice == m_size+3 ) { //return
        set_leave_menu_true();
    } else { //map choisie en choice-3

    }
}

void MenuJoin::update()
{
    Menu::update();
    updateNetwork();
}

void MenuJoin::refreshList()
{
    int i=0;
    m_menu_actions.clearList();
    m_menu_actions.add_action_string("IP", 1, "192.168.1.1");
    m_menu_actions.add_action_classic("Refresh", 2);

    std::map<std::string,std::string>::iterator it = gNetwork->beginServers();
    while ( it != gNetwork->endServers() ) {
        m_menu_actions.add_action_classic((*it).second, i+3);
        ++it;
        ++i;
    }
    m_size = i;
    m_menu_actions.add_action_classic("Return", m_size+3);
}
