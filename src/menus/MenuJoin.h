#ifndef _MENUJOIN_H
#define _MENUJOIN_H

#include "Menu.h"

class MenuJoin : public Menu
{
public:
    /**
     *  @brief Constructeur
     *  @param parent Le menu appelant
     */
    MenuJoin (Menu *parent);

    /**
     *  @brief Destructeur
     */
    ~MenuJoin();

    /**
     *	@brief Traitement du choix
     *	@param l'int correspond au numero de la liste choisi
     */
    virtual void treat_choice (int choice);

    /**
     *
     */
    void update();

    /**
     *  Met a jour la liste des parties decouvertes
     */
    void refreshList();

    /**
     *  Redef
     */
    void close();

private:
    int m_size; //nombre de parties decouvertes
};

#endif // _MENUJOIN_H
