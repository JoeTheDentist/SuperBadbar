#include "NetworkEntityMenu.h"

#include <QDebug>

NetworkEntityMenu::NetworkEntityMenu()
{
}

NetworkEntityMenu::~NetworkEntityMenu()
{
}

void NetworkEntityMenu::setToRefresh()
{
    //cast de ptr de methode... Ca marche ! (sans rire !)
    actionToActivate = (void (NetworkEntity::*)())&NetworkEntityMenu::refreshList;
}
