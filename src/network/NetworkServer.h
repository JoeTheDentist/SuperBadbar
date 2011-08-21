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

#define BROADCAST_FREQ 5000

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

    /***************************************/
    /****************Phases*****************/
    /***************************************/
public:
    /**
     *  @brief Phase de decouverte
     */
    void discovery();

    /***************************************/
    /*****************Treat*****************/
    /***************************************/
private:
    /**
     *  @brief Traite l'objet de demande de variable
     *  @param object : objet de demande de variable
     */
    void treatObject(const NetworkMessageAskFor &object);

    /***************************************/
    /*****************SLOTS*****************/
    /***************************************/
private slots:
    /**
     *  @brief Signale sur le reseau
     *
     *  Coucou ! Je suis là
     *  (Solo de Korn sur Another brick in the wall)
     *  Message envoye 4 fois (udp oblige), toutes les BROADCAST_FREQ ms
     * (timer)
     */
    void broadcastAd();

    /**
     *  @brief Nouvelle connexion
     */
    void newClient();


    /***************************************/
    /*****************Utile*****************/
    /***************************************/
private:
    /**
     *  S'assure de tout cleaner avant de lancer
     *  un nouvel etat
     */
    void clearState();


    /***************************************/
    /***************Attributs***************/
    /***************************************/
private:
    QTcpServer *m_server;
    QMap<int, QTcpSocket*> m_clients;
    QTimer *m_timer;

};

#endif // NETWORKSERVER_H
