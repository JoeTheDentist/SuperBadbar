#ifndef _BABAR_OPTIONS_MENU_H
#define _BABAR_OPTIONS_MENU_H

#include "menus/Menu.h"

#include "video/Surface.h"
#include "menus/ListMenuActions.h"


class OptionsMenu: public Menu
{
protected:



public:
    /*!
    *	@brief Constructeur
    *	@param parent Le menu appelant
    */
    OptionsMenu (Menu *parent = NULL);

    /*!
    *	@brief Destructeur
    */
    ~OptionsMenu();

    /*!
    *	@brief Mise a jour du menu (sauf affichage)
    */
    virtual void update();

protected:
    /*!
    *	@brief Lance le menu de configuration du clavier
    */
    virtual void launch_keyconfig();

    /*!
    *	@brief Traitement du choix
    *	@param l'int correspond au numero de la liste choisi
    */
    virtual void treat_choice (int choice);
};


#endif
