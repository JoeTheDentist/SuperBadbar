#include "MenuMulti.h"
#include "../menus/MenuJoin.h"

/* TEMP */ #include "../network/NetworkServer.h"

MenuMulti::MenuMulti(Menu *parent) :
        Menu(parent)
{
        m_menu_actions.add_action_classic("Join", 1);
        m_menu_actions.add_action_classic("Host", 2);
        m_menu_actions.add_action_classic("Return", 3);
}

MenuMulti::~MenuMulti()
{

}

void MenuMulti::treat_choice(int choice)
{
    switch(choice) {
	case 1: // join
		set_son(new MenuJoin(this));
		break;
	case 2: // host
            {
                NetworkServer *serv = new NetworkServer();
            }
		break;
	case 3: // return
		set_leave_menu_true();
		break;
	default:
		break;
    }
}
