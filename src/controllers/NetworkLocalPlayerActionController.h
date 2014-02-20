#ifndef NETWORKLOCALPLAYERACTIONCONTROLLER_H
#define NETWORKLOCALPLAYERACTIONCONTROLLER_H

#include "NetworkPlayerActionController.h"
#include "PlayerKeyboardActionController.h"

class NetworkLocalPlayerActionController : public NetworkPlayerActionController,
    public PlayerKeyboardActionController
{
public:
    NetworkLocalPlayerActionController();
};

#endif // NETWORKLOCALPLAYERACTIONCONTROLLER_H
