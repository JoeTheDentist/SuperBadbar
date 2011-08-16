#include "MenuHost.h"

#include <QDir>
#include <QStringList>
#include <QDebug>

#include "util/repertories.h"
#include "util/globals.h"
#include "network/NetworkManager.h"
#include "menus/MenuWaitForPlayers.h"

MenuHost::MenuHost(Menu *parent) :
        Menu(parent)
{
    gNetwork->initServer();
    m_menu_actions.add_action_classic("Return", 1);
    buildMenuWithLevels();
}

MenuHost::~MenuHost()
{

}

void MenuHost::treat_choice(int choice)
{
    if ( choice == 1 ) { //return
        set_leave_menu_true();
    } else { //choix d'une map
        selectLevel(choice-1);
    }
}

void MenuHost::buildMenuWithLevels()
{
    QDir files(QString::fromStdString(LEVELS_R));

    for (int i = 0; i < files.entryList(QDir::Files).size(); ++i) {
        m_lvls << files.entryList(QDir::Files).at(i);
        m_menu_actions.add_action_classic(files.entryList(QDir::Files).at(i).toStdString(), i+2);
    }
}

void MenuHost::selectLevel(int choice)
{
    set_son(new MenuWaitForPlayers(this, m_lvls[choice]));
}
