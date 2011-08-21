#ifndef NETWORKENTITYMENU_H
#define NETWORKENTITYMENU_H

#include "network/NetworkEntity.h"

class NetworkEntityMenu : public NetworkEntity
{
public:
    /**
     *  Constructeur
     */
    NetworkEntityMenu();

    /**
     *  Destructeur
     */
    virtual ~NetworkEntityMenu();

protected:
    /**
     *  Reaffiche liste des joueurs
     *  Liste contenue par player manager
     */
    virtual void refreshList()=0;

public:
    /**
     *  Mettre a rafraichir
     */
    void setToRefresh();


};

#endif // NETWORKENTITYMENU_H
