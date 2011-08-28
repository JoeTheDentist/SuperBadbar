#include "MenuWaitForPlayers.h"

#include "network/NetworkManager.h"
#include "util/globals.h"
#include "players/PlayersManager.h"


MenuWaitForPlayers::MenuWaitForPlayers(Menu *parent, QString lvl_name)
    :Menu(parent)
{
    gPlayers->setMap(lvl_name.toStdString());
    if ( gNetwork->isServer() ) { //role serveur
        gNetwork->startServer();
        m_lvlSelected = lvl_name;
        m_menu_actions.add_action_classic("Return", 1);
        m_menu_actions.add_action_classic(gPlayers->playerName(), 2);
    } else { //role client

    }
}

MenuWaitForPlayers::~MenuWaitForPlayers()
{

}

void MenuWaitForPlayers::treat_choice(int choice) {
    if ( gNetwork->isServer() ) { //role serveur
        if ( choice == 1 ) { //return
            //TODO deco les joueurs avant
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
    Menu::update();
    updateNetwork();
}

void MenuWaitForPlayers::refreshList()
{

}
