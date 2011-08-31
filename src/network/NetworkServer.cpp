#include "NetworkServer.h"

#include "NetworkTypes.h"
#include "players/PlayersManager.h"
#include "util/globals.h"
#include "util/debug.h"

NetworkServer::NetworkServer()
{
    m_numPlayer = 0;
    m_timer = NULL;
    m_server = NULL;
}

NetworkServer::~NetworkServer()
{
    clearState();
}

void NetworkServer::discovery()
{
    clearState();
    m_state = NS_DISCOVERY;
    broadcastAd();
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(broadcastAd()));
    m_timer->start(BROADCAST_FREQ);

    m_server = new QTcpServer(this);
    if (!m_server->listen(QHostAddress::Any, TCP_PORT)) {
        //error
    } else {
        connect(m_server, SIGNAL(newConnection()), this, SLOT(newClient()));
    }
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
    m_clients.insert(m_numPlayer, client);
    ++m_numPlayer;

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
    //clean si server lance
    clearServer();
}

void NetworkServer::discoAll()
{
    foreach ( QTcpSocket *client, m_clients ) {
        client->disconnectFromHost();
        //TOCHECK
        delete client;
    }
    m_clients.clear();
}

void NetworkServer::clearServer()
{
    discoAll();
    m_numPlayer = 0;
    m_clients.clear();
    delete m_server;
    m_server = NULL;
}
