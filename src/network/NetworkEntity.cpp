
#include "NetworkEntity.h"

#include "network/NetworkManager.h"
#include "util/globals.h"

unsigned int NetworkEntity::NetworkEntitiesCounter = 0;

NetworkEntity::NetworkEntity()
{
    m_id = NetworkEntitiesCounter;
    NetworkEntitiesCounter++;
    actionToActivate = &NetworkEntity::doNothing;
    gNetwork->addEntity(this);
}

NetworkEntity::~NetworkEntity()
{
}

int NetworkEntity::id()
{
    return m_id;
}

void NetworkEntity::ResetCounter()
{
    NetworkEntitiesCounter = 0;
}

void NetworkEntity::sigKilled()
{

}

void NetworkEntity::updateNetwork()
{
    (this->*NetworkEntity::actionToActivate)();
    actionToActivate = &NetworkEntity::doNothing;
}

void NetworkEntity::killed()
{

}
