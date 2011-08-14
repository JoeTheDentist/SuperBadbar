#ifndef MENUWAITFORPLAYERS_H
#define MENUWAITFORPLAYERS_H

#include <QString>

#include "menus/Menu.h"

class MenuWaitForPlayers : public Menu
{
public:
    /**
     *  Constructeur
     */
    MenuWaitForPlayers(Menu *parent, QString lvl_name);

    /**
     *  Destructeur
     */
    ~MenuWaitForPlayers();

    /**
     *  Choix
     */
    void treat_choice(int choice);

private:
    QString m_lvlSelected;
};

#endif // MENUWAITFORPLAYERS_H
