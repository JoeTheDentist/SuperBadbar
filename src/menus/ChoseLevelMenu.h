
#ifndef _CHOSELEVELMENU_H_
#define _CHOSELEVELMENU_H_

#include <menus/Menu.h>

class ChoseLevelMenu: public Menu
{
public:
    /**
     *  @brief Constructeur
     *  @param parent Le menu appelant
     */
    ChoseLevelMenu (Menu *parent);

protected:


    /*!
    *	@brief Traitement du choix
    *	@param l'int correspond au numero de la liste choisi
    */
    virtual void treat_choice (int choice);
};


#endif
