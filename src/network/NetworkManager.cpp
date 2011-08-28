
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
    m_netCom = NULL;
    m_id_menu = 0;
    NetworkEntity::ResetCounter();
    m_server = false;
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
    m_servers.insert(std::pair<std::string,std::string>(ip, adMsg));
    NetworkEntity *ne = (*m_entities.find(m_id_menu)).second;
    NetworkEntityMenu *menu = dynamic_cast<NetworkEntityMenu*>(ne);
    if ( menu ) {
        menu->setToRefresh();
    }
}

std::map<std::string,std::string>::iterator NetworkManager::beginServers()
{
    return m_servers.begin();
}

std::map<std::string,std::string>::iterator NetworkManager::endServers()
{
    return m_servers.end();
}
