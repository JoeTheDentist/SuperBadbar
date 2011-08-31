
#include "util/debug.h"

#include "NetworkCommunicator.h"
#include "util/globals.h"
#include "network/NetworkManager.h"

NetworkCommunicator::NetworkCommunicator()
{
    m_msgSize = 0;
    m_udpReceivingSocket = new QUdpSocket(this);
    m_udpSendingSocket = new QUdpSocket(this);
    connect(m_udpReceivingSocket, SIGNAL(readyRead()), this, SLOT(receivingUdpData()));
    m_state = NS_NONE;
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
        getAndTreatIncomingUdpObjects(socket);
    }
}

void NetworkCommunicator::receivingTcpData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    while ( socket->bytesAvailable() ) {
        getAndTreatIncomingTcpObjects(socket);
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
        treatAdObject(msg);
        return;
    } else if ( type == qMetaTypeId<NetworkMessageAskFor>() ) {
        NetworkMessageAskFor msg = object.value<NetworkMessageAskFor>();
        treatObject(msg);
    } else if ( type == qMetaTypeId<NetworkMessageResponse>() ) {
        NetworkMessageResponse msg = object.value<NetworkMessageResponse>();
        treatObject(msg);
    } else if ( type == qMetaTypeId<NetworkMessageConnexion>() ) {
        NetworkMessageConnexion msg = object.value<NetworkMessageConnexion>();
        treatObjectConnexion(msg);
    } else {
        PRINT_DEBUG(1, "Type non trouve : code Gloups est une chique !");
    }
}

void NetworkCommunicator::treatObject(const NetworkMessageError &object)
{
    QString msg = QString("Erreur reseau : ")+object.errorMsg;
    PRINT_DEBUG(1, "%s", (msg.toStdString()).c_str());
}

void NetworkCommunicator::treatAdObject(const NetworkMessageAd &object)
{
    //on ne recoit des messages d'ad que lorsqu'on est client et en discovery
    if ( m_state == NS_DISCOVERY && !gNetwork->isServer() ) {
        gNetwork->addAd(m_lastIp, object.adMsg.toStdString());
    }
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

void NetworkCommunicator::treatObjectConnexion(const NetworkMessageConnexion &object) {
    if ( m_state == NS_DISCOVERY && gNetwork->isServer() ) {
        //Rafraichir et envoyer l'info a ttlm
        gNetwork->addPlayer(/*TODO*/1, object.name.toStdString());
    }
}


/***************************************/
/******Envoie/reception d'objets********/
/***************************************/

void NetworkCommunicator::sendObject(const QVariant &object, QTcpSocket *socket)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    //TODO mettre un QByteArray compresse a la place de object
    out << (quint16) 0;
    out << object;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    //QByteArray data = qCompress(paquet);

    socket->write(paquet);
}

void NetworkCommunicator::sendObject(const QVariant &object, QUdpSocket *socket,
                                     const QHostAddress &address)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << object;

    QByteArray data = qCompress(paquet);

    socket->write(data);

    if ( gNetwork->isServer() ) {
        socket->writeDatagram(data, address, PORT_SERVER_OUT);
    } else {
        socket->writeDatagram(data, address, PORT_SERVER_IN);
    }
}

void NetworkCommunicator::getAndTreatIncomingUdpObjects(QUdpSocket *socket)
{
    QHostAddress sender;
    quint16 port;

    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &port);
        QByteArray uncompresseData = qUncompress(datagram);
        QDataStream in(&uncompresseData, QIODevice::ReadOnly);

        m_lastIp = sender.toString().toStdString();

        QVariant object;
        in >> object;

        treatObject(object);
    }
}

void NetworkCommunicator::getAndTreatIncomingTcpObjects(QTcpSocket *socket)
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
