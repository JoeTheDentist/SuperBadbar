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

#include "network/NetworkCommunicator.h"

/**
 *  @class NetworkClient
 *  @brief Classe client
 */
class NetworkClient : public NetworkCommunicator
{
    /***************************************/
    /**************Attributs****************/
    /***************************************/
private:
    QTcpSocket *m_TcpSocket;

public:
    /**
     *  @brief Constructeur
     */
    NetworkClient();

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkClient();

    /***************************************/
    /****************Phases*****************/
    /***************************************/
public:
    /**
     *  @brief Phase de decouverte
     */
    void discovery();

    /**
     *  @brief Phase d'attente des joueurs
     */
    void waitForPlayers();

    /**
     *  Tentative de connection a l'adress ip
     *  passe en mode waitForPlayers
     */
    void connectTo(const std::string &ip);

    /***************************************/
    /****************Autre******************/
    /***************************************/
public:
    /**
     *  S'assure de tout cleaner avant de lancer
     *  un nouvel etat
     */
    void clearState();

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
