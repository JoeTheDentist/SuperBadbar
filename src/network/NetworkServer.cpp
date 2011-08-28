#include "NetworkServer.h"

#include "NetworkTypes.h"
#include "players/PlayersManager.h"
#include "util/globals.h"
#include "util/debug.h"

NetworkServer::NetworkServer()
{
    m_timer = NULL;
}

NetworkServer::~NetworkServer()
{
    if ( m_timer )
        m_timer->stop();
    delete m_timer;
}

void NetworkServer::discovery()
{
    clearState();
    m_state = NS_DISCOVERY;
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(broadcastAd()));
    m_timer->start(BROADCAST_FREQ);
}

void NetworkServer::treatObject(const NetworkMessageAskFor &object)
{

}

void NetworkServer::broadcastAd()
{
    NetworkMessageAd msg(QString::fromStdString(gPlayers->playerName())+" - "+
                         QString::fromStdString(gPlayers->getMap()));
    QVariant v;
    v.setValue(msg);
    for (int i = 0; i<4; i++) {
        sendObject(v, m_udpSendingSocket, QHostAddress::Broadcast);
    }
}

void NetworkServer::newClient()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    m_clients.insert(/* TODO */ 1, client);

    connect(client, SIGNAL(readyRead()), this, SLOT(receivingTcpData()));
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

void NetworkServer::clearState()
{
    //clean si etat discovery
    if ( m_timer ) {
        m_timer->stop();
        delete m_timer;
        m_timer = NULL;
    }
}
