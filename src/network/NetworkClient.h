/**
 * 	@file NetworkClient.h
 * 	@brief header de la classe NetworkClient
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "NetworkCommunicator.h"

/**
 *  @class NetworkClient
 *  @brief Classe client
 */
class NetworkClient : public NetworkCommunicator
{
public:
    /**
     *  @brief Constructeur
     */
    NetworkClient();

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkClient();

private:
    /**
     *  @brief Traite l'objet de pub
     *  @param object : objet de pub
     */
    void treatObject(const NetworkMessageAd &object);

    /**
     *  @brief Traite l'objet de demande de variable
     *  @param object : objet de demande de variable
     */
    void treatObject(const NetworkMessageAskFor &object);
};

#endif // NETWORKCLIENT_H
