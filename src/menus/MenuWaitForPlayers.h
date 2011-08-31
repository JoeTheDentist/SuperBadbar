#ifndef MENUWAITFORPLAYERS_H
#define MENUWAITFORPLAYERS_H

#include <QString>

#include "menus/Menu.h"
#include "network/NetworkEntityMenu.h"

class MenuWaitForPlayers : public Menu, public NetworkEntityMenu
{
public:
    /**
     *  Constructeur
     */
    MenuWaitForPlayers(Menu *parent, QString lvl_name = "");

    /**
     *  Destructeur
     */
    virtual ~MenuWaitForPlayers();

    /**
     *  Choix
     */
    void treat_choice(int choice);

    /**
     *  Redef
     */
    void update();

    /**
     *  Redef
     */
    void refreshList();

    /**
     *  Redef
     */
    void close();

private:
    QString m_lvlSelected;
};

#endif // MENUWAITFORPLAYERS_H
