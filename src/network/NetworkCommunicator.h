/**
 * 	@file NetworkCommunicator.h
 * 	@brief header de la classe NetworkCommunicator
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juillet 2011
 *
 */

#ifndef NETWORKCOMMUNICATOR_H
#define NETWORKCOMMUNICATOR_H

#include <QVariant>
#include <QtNetwork>

#include "network/NetworkTypes.h"

enum NetworkState {
    NS_DISCOVERY, NS_WAITFORPLAYERS
};

/**
 *  @class NetworkCommunicator
 *  @brief Classe abstraite representant un tuyau de communication
 *
 *  Cette classe peut jouer le role d'un client ou d'un serveur
 */
class NetworkCommunicator : public QObject
{
    Q_OBJECT

public:
    /**
     *  @brief Constructeur
     */
    NetworkCommunicator();

    /**
     *  @brief Destructeur
     */
    virtual ~NetworkCommunicator();

    /***************************************/
    /****************Phases*****************/
    /***************************************/
public:
    /**
     *  @brief Phase de decouverte
     */
    virtual void discovery() = 0;


    /***************************************/
    /*****************SLOTS*****************/
    /***************************************/
protected slots:
    /**
     *  @brief Traite en fonction de l'objet reçu (UDP)
     */
    virtual void receivingUdpData();

    /**
     *  @brief Traite en fonction de l'objet reçu (TCP)
     */
    virtual void receivingTcpData();

    /***************************************/
    /***Communication avec NetworkManager***/
    /***************************************/
private:
    /**
     *  @brief Traite l'objet
     *  @param object : objet a traiter
     */
    void treatObject(const QVariant &object);

protected:
    /**
     *  @brief Traite l'objet d'erreur
     *  @param object : objet d'erreur
     *
     *  Pas besoin de redef
     */
    void treatObject(const NetworkMessageError &object);

    /**
     *  @brief Traite l'objet de pub
     *  @param object : objet de pub
     *
     *  PRINT_DEBUG si non redef (seul les clients peuvent traiter)
     */
    virtual void treatObject(const NetworkMessageAd &object);

    /**
     *  @brief Traite l'objet de demande de variable
     *  @param object : objet de demande de variable
     */
    virtual void treatObject(const NetworkMessageAskFor &object);

    /**
     *  @brief Traite l'objet de reponse
     *  @param object : objet de reponse
     */
    void treatObject(const NetworkMessageResponse &object);


    /***************************************/
    /******Envoie/reception d'objets********/
    /***************************************/
protected:
    /**
     *  @brief Envoie un objet sur la socket (tcp)
     *  @param object : objet a envoyer
     *  @param socket : socket sur laquelle envoyer
     *
     *  La strategie d'envoi est faite en fonction
     *  de l'objet et du type de communicator
     *  (client ou serveur)
     */
    virtual void sendObject(const QVariant &object, QTcpSocket *socket);

    /**
     *  @brief Envoie un objet sur la socket (udp)
     *  @param object : objet a envoyer
     *  @param socket : socket sur laquelle envoyer
     *  @param address : destination de l'objet
     *
     *  La strategie d'envoi est faite en fonction
     *  de l'objet et du type de communicator
     *  (client ou serveur)
     */
    virtual void sendObject(const QVariant &object, QUdpSocket *socket,
                            const QHostAddress &address);

    /**
     *  @brief Recupere les objets sur une socket et le traite
     *  @param socket : socket à lire
     *
     *  Peut ne pas marcher, QAbstractSocket (tocheck)
     */
    void getAndTreatIncomingObjects(QAbstractSocket *socket);


    /***************************************/
    /**************Attributs****************/
    /***************************************/
protected:
    QUdpSocket *m_udpSendingSocket;
    QUdpSocket *m_udpReceivingSocket;
    unsigned int m_msgSize;
    NetworkState m_state;
};

#endif // NETWORKCOMMUNICATOR_H
