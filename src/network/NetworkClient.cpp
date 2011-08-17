#include "NetworkClient.h"

NetworkClient::NetworkClient()
{

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
