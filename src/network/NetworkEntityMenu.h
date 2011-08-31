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

    /**
     *  Forcer la fermeture du menu
     */
    virtual void close()=0;

public:
    /**
     *  Mettre a rafraichir
     */
    void setToRefresh();

    /**
     *  Mettre a fermer
     *  A utiliser par exemple quand deco
     */
    void setToClose();


};

#endif // NETWORKENTITYMENU_H
