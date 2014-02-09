#include "ControllerManager.h"

#include "MenuKeyboardActionController.h"
#include "NetworkMenuActionController.h"
#include "PlayerKeyboardActionController.h"
#include "NetworkLocalPlayerActionController.h"
#include "NetworkRemotePlayerActionController.h"

using namespace std;

ControllerManager *ControllerManager::s_instance = 0;

ControllerManager *ControllerManager::GetInstance()
{
    if (!s_instance)
    {
        s_instance = new ControllerManager();
    }
    return s_instance;
}

void ControllerManager::Destroy()
{
    delete s_instance;
    s_instance = 0;
}

MenuKeyboardActionController *
ControllerManager::createMenuKeyboardActionController()
{
    MenuKeyboardActionController *ctr = new MenuKeyboardActionController();
    m_controllers.push_back (ctr);
    return ctr;
}

NetworkMenuActionController *
ControllerManager::createNetworkMenuActionController()
{
    NetworkMenuActionController *ctr = new NetworkMenuActionController();
    m_controllers.push_back (ctr);
    return ctr;
}

PlayerKeyboardActionController *
ControllerManager::createPlayerKeyboardActionController()
{
    PlayerKeyboardActionController *ctr = new PlayerKeyboardActionController();
    m_controllers.push_back (ctr);
    return ctr;
}

NetworkLocalPlayerActionController *
ControllerManager::createNetworkLocalPlayerActionController()
{
    NetworkLocalPlayerActionController *ctr =
        new NetworkLocalPlayerActionController();
    m_controllers.push_back (ctr);
    return ctr;
}

NetworkRemotePlayerActionController *
ControllerManager::createNetworkRemotePlayerActionController()
{
    NetworkRemotePlayerActionController *ctr =
        new NetworkRemotePlayerActionController();
    m_controllers.push_back (ctr);
    return ctr;
}

ControllerManager::ControllerManager()
{
}

ControllerManager::~ControllerManager()
{
    for (list<Controller*>::iterator it = m_controllers.begin();
            it != m_controllers.end();
            ++it)
    {
        delete (*it);
    }
}
