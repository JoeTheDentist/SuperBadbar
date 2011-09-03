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
    //TODO p-e passer la socket, pour renvoyer juste au demandeur
    if ( object.varName == "players" ) {
        QStringList list;
        std::list<std::string>::iterator it = gNetwork->beginPlayers();
        while ( it != gNetwork->endPlayers() ) {
            list << QString::fromStdString(*it);
            ++it;
        }
        NetworkMessageResponse resp;
        resp.respVar = NetworkTypes::toQVariant(list);
        sendObjectToAll(NetworkTypes::toQVariant(resp));
    } else {
        PRINT_DEBUG(1, "Non implemente : code vive Joe Joseph !");
    }
}

void NetworkServer::broadcastAd()
{
    NetworkMessageAd msg(QString::fromStdString(gPlayers->playerName())+" - "+
                         QString::fromStdString(gPlayers->getMap()));
    for (int i = 0; i<4; i++) {
        sendObject(NetworkTypes::toQVariant(msg), m_udpSendingSocket, QHostAddress::Broadcast);
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

void NetworkServer::sendObjectToAll(const QVariant &object)
{
    foreach( QTcpSocket *socket, m_clients) {
        sendObject(object,socket);
    }
}

void NetworkServer::clientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    qDebug() << socket->peerAddress().toString() << " disco";
}
