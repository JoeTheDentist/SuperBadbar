#include "NetworkEntity.h"

unsigned int NetworkEntity::NetworkEntitiesCounter = 0;

NetworkEntity::NetworkEntity()
{
    m_id = NetworkEntitiesCounter;
    NetworkEntitiesCounter++;
}

NetworkEntity::~NetworkEntity()
{
}

void NetworkEntity::ResetCounter()
{
    NetworkEntitiesCounter = 0;
}
