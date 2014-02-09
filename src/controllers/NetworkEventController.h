#ifndef NETWORKEVENTCONTROLLER_H
#define NETWORKEVENTCONTROLLER_H

#include "EventController.h"
#include "network/NetworkController.h"

class NetworkEventController : virtual public EventController,
    public NetworkController
{
public:
    NetworkEventController();
};

#endif // NETWORKEVENTCONTROLLER_H
