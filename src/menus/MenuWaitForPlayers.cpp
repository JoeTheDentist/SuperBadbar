#include "MenuWaitForPlayers.h"

#include "network/NetworkManager.h"
#include "util/globals.h"
#include "players/PlayersManager.h"


MenuWaitForPlayers::MenuWaitForPlayers(Menu *parent, QString lvl_name)
    :Menu(parent)
{
    m_menu_actions.add_action_classic("Return", 1);
    gPlayers->setMap(lvl_name.toStdString());
    if ( gNetwork->isServer() ) { //role serveur
        gNetwork->startServer();
        m_lvlSelected = lvl_name;
        gNetwork->addPlayer(gPlayers->playerName());
    } else { //role client
        gNetwork->getAndDisplayPlayers();
    }
}

MenuWaitForPlayers::~MenuWaitForPlayers()
{

}

void MenuWaitForPlayers::treat_choice(int choice) {
    if ( gNetwork->isServer() ) { //role serveur
        if ( choice == 1 ) { //return
            gNetwork->discoAll();
            set_leave_menu_true();
        }
    } else { //role client
        if ( choice == 1 ) { //return
            set_leave_menu_true();
        }
    }
}

void MenuWaitForPlayers::update()
{
    gNetwork->setMenuId(m_id);
    Menu::update();
    updateNetwork();
}

void MenuWaitForPlayers::refreshList()
{
    int i=0;
    m_menu_actions.clearList();
    m_menu_actions.add_action_classic("Return", 1);

    std::list<std::string>::iterator it = gNetwork->beginPlayers();
    while ( it != gNetwork->endPlayers() ) {
        m_menu_actions.add_action_classic((*it), i+2);
        ++it;
    }
}

void MenuWaitForPlayers::close()
{
    set_leave_menu_true();
}
