#include "NetworkClient.h"

NetworkClient::NetworkClient()
{
    m_udpReceivingSocket->bind(PORT_SERVER_OUT, QUdpSocket::ShareAddress);
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::discovery()
{
    m_state = NS_DISCOVERY;
}

void NetworkClient::treatObject(const NetworkMessageAd &object)
{

}

void NetworkClient::treatObject(const NetworkMessageAskFor &object)
{

}
