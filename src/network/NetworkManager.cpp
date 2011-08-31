
#include "NetworkManager.h"
#include "NetworkClient.h"
#include "NetworkServer.h"
#include "util/debug.h"
#include "NetworkCommunicator.h"
#include "NetworkEntity.h"
#include "NetworkEntityMenu.h"

#include <QDebug> //TEMP

NetworkManager::NetworkManager()
{   
    PRINT_CONSTR(1, "Construction d'un NetworkManager");

    NetworkTypes::initNetTypes();
    m_netCom = NULL;
    m_id_menu = 0;
    NetworkEntity::ResetCounter();
    m_server = false;
    m_netStep = NetStepNONE;
}

NetworkManager::~NetworkManager()
{
    PRINT_CONSTR(1, "Destruction d'un NetworkManager");
    delete m_netCom;
}

void NetworkManager::initClient()
{
    delete m_netCom;
    m_netCom = new NetworkClient();
    m_server = false;
    m_netCom->discovery();
}

void NetworkManager::initServer()
{
    delete m_netCom;
    m_netCom = new NetworkServer();
    m_server = true;
}

void NetworkManager::startServer()
{
    m_netCom->discovery();
}

bool NetworkManager::isServer()
 {
    return m_server;
}

void NetworkManager::addEntity(NetworkEntity *ne)
{
    m_entities.insert(std::pair<int,NetworkEntity*>(ne->id(), ne));
}

void NetworkManager::addAd(const std::string &ip, const std::string &adMsg)
{
    if ( m_servers.find(ip) == m_servers.end() ) {
        m_servers.insert(std::pair<std::string,std::string>(ip, adMsg));
        NetworkEntity *ne = (*m_entities.find(m_id_menu)).second;
        NetworkEntityMenu *menu = dynamic_cast<NetworkEntityMenu*>(ne);
        if ( menu ) {
            menu->setToRefresh();
        }
    }
}

void NetworkManager::connectTo(const std::string &ip)
{
    if ( !m_server ) {
        NetworkClient *client = dynamic_cast<NetworkClient*>(m_netCom);
        client->connectTo(ip);
    }
}

void NetworkManager::setMenuId(int id)
{
    m_id_menu = id;
}

std::map<std::string,std::string>::iterator NetworkManager::beginServers()
{
    return m_servers.begin();
}

std::map<std::string,std::string>::iterator NetworkManager::endServers()
{
    return m_servers.end();
}

std::list<std::string>::iterator NetworkManager::beginPlayers()
{
    return m_players.begin();
}

std::list<std::string>::iterator NetworkManager::endPlayers()
{
    return m_players.end();
}

void NetworkManager::clearServers()
{
    m_servers.clear();
}

void NetworkManager::clearPlayers()
{
    m_players.clear();
}

void NetworkManager::addPlayer(std::string name)
{
    m_players.push_front(name);
    NetworkEntity *ne = (*m_entities.find(m_id_menu)).second;
    NetworkEntityMenu *menu = dynamic_cast<NetworkEntityMenu*>(ne);
    if ( menu ) {
        menu->setToRefresh();
    }
}

void NetworkManager::getAndDisplayPlayers()
{
    connectTo(m_hostIp);
}

void NetworkManager::discoAll()
{
    if ( m_server ) {
        NetworkServer *server = dynamic_cast<NetworkServer*>(m_netCom);
        server->discoAll();
    }
}

void NetworkManager::setHostIp(std::string ip)
{
    m_hostIp = ip;
}

void NetworkManager::clearAll()
{
    m_servers.clear();
    m_players.clear();
    m_netCom->clearState();
}
