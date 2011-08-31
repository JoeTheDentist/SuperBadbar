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
    m_TcpSocket->abort();
    m_TcpSocket->connectToHost(QString::fromStdString(ip), TCP_PORT);
    NetworkMessageConnexion connexion(QString::fromStdString(gPlayers->playerName()));
    QVariant object;
    object.setValue(connexion);
    sendObject(object, m_TcpSocket);
}

void NetworkClient::clearState()
{
    m_TcpSocket->disconnectFromHost();
    delete m_TcpSocket;
    m_TcpSocket = NULL;
}
