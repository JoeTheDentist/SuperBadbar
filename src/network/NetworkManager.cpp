
#include "NetworkManager.h"
#include "NetworkClient.h"
#include "NetworkServer.h"
#include "../util/debug.h"

NetworkManager::NetworkManager()
{
    PRINT_CONSTR(1, "Construction d'un NetworkManager");
    m_netCom = NULL;
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
}

void NetworkManager::initServer()
{
    delete m_netCom;
    m_netCom = new NetworkServer();
}
