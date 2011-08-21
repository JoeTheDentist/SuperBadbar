#ifndef _MENUJOIN_H
#define _MENUJOIN_H

#include "Menu.h"
#include "network/NetworkEntityMenu.h"

class MenuJoin : public Menu, public NetworkEntityMenu
{
public:
    /**
     *  @brief Constructeur
     *  @param parent Le menu appelant
     */
    MenuJoin(Menu *parent);

    /**
     *  @brief Destructeur
     */
    ~MenuJoin();

    /**
    *	@brief Traitement du choix
    *	@param l'int correspond au numero de la liste choisi
    */
    virtual void treat_choice(int choice);

    /**
     *
     */
    void refreshList();
};

#endif // _MENUJOIN_H
