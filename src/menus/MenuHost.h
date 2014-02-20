#ifndef MENUHOST_H
#define MENUHOST_H

#include <list>
#include <string>

#include "menus/Menu.h"

class MenuHost : public Menu
{
public:
    /**
     *  Constructeur
     */
    MenuHost (Menu *parent);

    /**
     *  Destructeur
     */
    ~MenuHost();

    /**
     *  Choix
     */
    void treat_choice (int choice);

private:
    /**
     *  Construit le menu en fonction de ce qu'il
     *  y a dans ../data/levels
     */
    void buildMenuWithLevels();

    /**
     *  Lance le menu d'attente avec le niveau choisi
     */
    void selectLevel (int choice);

private:
    std::list<std::string> m_lvls;
};

#endif // MENUHOST_H
