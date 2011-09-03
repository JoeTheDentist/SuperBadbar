#include "NetworkClient.h"

#include "util/globals.h"
#include "players/PlayersManager.h"

NetworkClient::NetworkClient()
{
    m_TcpSocket = NULL;
    m_udpReceivingSocket->bind(PORT_SERVER_OUT, QUdpSocket::ShareAddress);
}

NetworkClient::~NetworkClient()
{
    clearState();
}

void NetworkClient::discovery()
{
    delete m_TcpSocket;
    m_TcpSocket = NULL;
    m_state = NS_DISCOVERY;
}

void NetworkClient::treatObject(const NetworkMessageAd &object)
{

}

void NetworkClient::treatObject(const NetworkMessageAskFor &object)
{

}

void NetworkClient::connectTo(const std::string &ip)
{
    m_TcpSocket = new QTcpSocket(this);
    connect(m_TcpSocket, SIGNAL(readyRead()), this, SLOT(receivingTcpData()));
    connect(m_TcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_TcpSocket, SIGNAL(disconnected()), this, SLOT(disco()));
    m_TcpSocket->abort();
    m_TcpSocket->connectToHost(QString::fromStdString(ip), TCP_PORT);

    NetworkMessageConnexion connexion(QString::fromStdString(gPlayers->playerName()));
    sendObject(NetworkTypes::toQVariant(connexion), m_TcpSocket);

    NetworkMessageAskFor ask("players");
    sendObject(NetworkTypes::toQVariant(ask), m_TcpSocket);
}

void NetworkClient::clearState()
{
    m_TcpSocket->disconnectFromHost();
    delete m_TcpSocket;
    m_TcpSocket = NULL;
}

void NetworkClient::connected()
{

}

void NetworkClient::disco()
{
    gNetwork->disco();
}
