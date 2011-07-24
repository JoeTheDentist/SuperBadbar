#ifndef _MENUMULTI_H
#define _MENUMULTI_H

#include "Menu.h"

class MenuMulti : public Menu
{
public:
    /**
     *  @brief Constructeur
     *  @param parent Le menu appelant
     */
    MenuMulti(Menu *parent);

    /**
     *  @brief Destructeur
     */
    ~MenuMulti();

    /**
    *	@brief Traitement du choix
    *	@param l'int correspond au numero de la liste choisi
    */
    virtual void treat_choice(int choice);
};

#endif // MENUMULTI_H
