#include "NetworkCommunicator.h"

NetworkCommunicator::NetworkCommunicator()
{
    connect(m_UDPReceivingSocket, SIGNAL(readyRead()), this, SLOT(receiveUDPObject()));
}

NetworkCommunicator::~NetworkCommunicator()
{

}

void NetworkCommunicator::getIncomingObject(QVariant &object, QAbstractSocket &socket)
{

}

