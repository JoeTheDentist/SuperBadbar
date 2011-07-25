
#include "../util/debug.h"

#include "NetworkCommunicator.h"

NetworkCommunicator::NetworkCommunicator()
{
    m_msgSize = 0;
    m_udpReceivingSocket = new QUdpSocket();
    m_udpSendingSocket = new QUdpSocket();
    connect(m_udpReceivingSocket, SIGNAL(readyRead()), this, SLOT(receivingUdpData()));
}

NetworkCommunicator::~NetworkCommunicator()
{
    delete m_udpReceivingSocket;
    delete m_udpSendingSocket;
}

/***************************************/
/****************SLOTS******************/
/***************************************/

void NetworkCommunicator::receivingUdpData()
{
    QUdpSocket *socket = qobject_cast<QUdpSocket *>(sender());
    while ( socket->bytesAvailable() ) {
        getAndTreatIncomingObjects(socket);
    }
}

void NetworkCommunicator::receivingTcpData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    while ( socket->bytesAvailable() ) {
        getAndTreatIncomingObjects(socket);
    }
}


/***************************************/
/***Communication avec NetworkManager***/
/***************************************/

void NetworkCommunicator::treatObject(const QVariant &object)
{
    int type = QMetaType::type(object.typeName());
    if ( type == qMetaTypeId<NetworkMessageError>() ) {
        NetworkMessageError msg = object.value<NetworkMessageError>();
        treatObject(msg);
        return;
    } else if ( type == qMetaTypeId<NetworkMessageAd>() ) {
        NetworkMessageAd msg = object.value<NetworkMessageAd>();
        treatObject(msg);
        return;
    } else if ( type == qMetaTypeId<NetworkMessageAskFor>() ) {
        NetworkMessageAskFor msg = object.value<NetworkMessageAskFor>();
        treatObject(msg);
    } else if ( type == qMetaTypeId<NetworkMessageResponse>() ) {
        NetworkMessageResponse msg = object.value<NetworkMessageResponse>();
        treatObject(msg);
    } else {
        PRINT_DEBUG(1, "Type non trouve : code Gloups est une chique !");
    }
}

void NetworkCommunicator::treatObject(const NetworkMessageError &object)
{
    QString msg = QString("Erreur reseau")+object.errorMsg;
    PRINT_DEBUG(1, msg.toStdString().c_str());
}

void NetworkCommunicator::treatObject(const NetworkMessageAd &object)
{
    PRINT_DEBUG(1, "Erreur objet d'ad traite par un serveur");
}

void NetworkCommunicator::treatObject(const NetworkMessageAskFor &object)
{
}

void NetworkCommunicator::treatObject(const NetworkMessageResponse &object)
{
    int type = QMetaType::type(object.respVar.typeName());
    if ( type == qMetaTypeId<int>() ) {
        // TODO
    } else {
        PRINT_DEBUG(1, "Type non trouve : code Crapatchou !");
    }
}


/***************************************/
/******Envoie/reception d'objets********/
/***************************************/

void NetworkCommunicator::sendObject(const QVariant &object, QTcpSocket *socket)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << object;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet);
}

void NetworkCommunicator::sendObject(const QVariant &object, QUdpSocket *socket,
                                     const QHostAddress &address)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << object;

    socket->writeDatagram(paquet, address, /* TODO */ (quint16)66666);
}

void NetworkCommunicator::getAndTreatIncomingObjects(QAbstractSocket *socket)
{
    QDataStream in(socket);

    while ( socket->bytesAvailable() ) {
        if ( m_msgSize == 0 ) {
            if ( socket->bytesAvailable() < (int)sizeof(quint16) )
                return;

            in >> m_msgSize;
        }

        if ( socket->bytesAvailable() < m_msgSize )
            return;

        QVariant object;
        in >> object;

        m_msgSize = 0;

        treatObject(object);
    }
}

