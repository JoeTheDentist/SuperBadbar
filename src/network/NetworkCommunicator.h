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

enum NetworkMessage {
    NetMsg_Texte, NetMsg_Position, NetMsg_
};

/**
 *  @class NetworkCommunicator
 *  @brief Classe abstraite reprÃ©sentant un tuyau de communication
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
    /**********Partie découverte************/
    /***************************************/

    /**
     *  @brief Envoie un QVariant sur le réseau
     *  @param Objet a envoyer
     */
    virtual void sendObject(QVariant object) = 0;

    /**
     *  @brief
     */
    virtual void getIncomingObject(QVariant &object, QAbstractSocket &socket);


protected slots:
    /**
     *  @brief Traite en fonction de l'objet reçu (UDP)
     */
    virtual void receiveUDPObject() = 0;

    /**
     *  @brief Traite en fonction de l'objet reçu (TCP)
     */
    virtual void receiveTCPObject() = 0;

protected:
    QUdpSocket *m_UDPSendingSocket;
    QUdpSocket *m_UDPReceivingSocket;

    /***************************************/
    /***Communication avec NetworkManager***/
    /***************************************/


};

#endif // NETWORKCOMMUNICATOR_H
