/**
 * 	@file NetworkServer.h
 * 	@brief header de la classe NetworkClient
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include "NetworkCommunicator.h"

class NetworkServer : public NetworkCommunicator
{
    Q_OBJECT

public:

    /**
     *  @brief Constructeur
     */
    NetworkServer();

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkServer();

protected:
    QTcpServer * m_server;
    QMap<int, QTcpSocket*> m_clients;

};

#endif // NETWORKSERVER_H
