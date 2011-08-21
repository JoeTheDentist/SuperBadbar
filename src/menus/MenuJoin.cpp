#include "MenuJoin.h"
#include "util/globals.h"
#include "network/NetworkManager.h"

MenuJoin::MenuJoin(Menu *parent) :
        Menu(parent)
{
    gNetwork->initClient();
    m_menu_actions.add_action_string("IP", 1, "192.168.1.1");
    m_menu_actions.add_action_classic("Refresh", 2);
    m_menu_actions.add_action_classic("Return", 3);
}

MenuJoin::~MenuJoin()
{

}

void MenuJoin::treat_choice(int choice)
{
    switch(choice) {
    case 1: // join
        break;
    case 2: // refresh
        break;
    case 3: // return
        set_leave_menu_true();
        break;
    default:
        break;
    }
}

void MenuJoin::refreshList()
{

}
