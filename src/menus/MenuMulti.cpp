#include "MenuMulti.h"

#include "menus/MenuJoin.h"
#include "menus/MenuHost.h"
#include "util/globals.h"
#include "network/NetworkManager.h"

MenuMulti::MenuMulti(Menu *parent) :
        Menu(parent)
{
    gNetwork = new NetworkManager();
    m_menu_actions.add_action_classic("Join", 1);
    m_menu_actions.add_action_classic("Host", 2);
    m_menu_actions.add_action_classic("Return", 3);
}

MenuMulti::~MenuMulti()
{
    delete gNetwork;
    gNetwork = NULL;
}

void MenuMulti::treat_choice(int choice)
{
    switch(choice) {
    case 1: // join
        set_son(new MenuJoin(this));
        break;
    case 2: // host
        set_son(new MenuHost(this));
        break;
    case 3: // return
        //suppr du reseau puisqu'on sort du menu
        delete gNetwork;
        gNetwork = NULL;
        set_leave_menu_true();
        break;
    default:
        break;
    }
}
