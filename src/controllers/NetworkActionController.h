#ifndef NETWORKACTIONCONTROLLER_H
#define NETWORKACTIONCONTROLLER_H

#include "ActionController.h"
#include "network/NetworkController.h"

class NetworkActionController : virtual public ActionController,
    public NetworkController
{
public:
    NetworkActionController();
};

#endif // NETWORKACTIONCONTROLLER_H
