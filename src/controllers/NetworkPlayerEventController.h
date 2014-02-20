#ifndef NETWORKPLAYEREVENTCONTROLLER_H
#define NETWORKPLAYEREVENTCONTROLLER_H

#include "PlayerEventController.h"
#include "NetworkEventController.h"

class NetworkPlayerEventController : public PlayerEventController,
    public NetworkEventController
{
public:
    NetworkPlayerEventController();
};

#endif // NETWORKPLAYEREVENTCONTROLLER_H
