#include "MenuJoin.h"

MenuJoin::MenuJoin(Menu *parent) :
        Menu(parent)
{
        m_menu_actions.add_action_string("IP", 1, "192.168.1.1");
        m_menu_actions.add_action_classic("Host", 2);
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
            case 2: // host
                    break;
            case 3: // return
                    set_leave_menu_true();
                    break;
            default:
                    break;
    }
}
