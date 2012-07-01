#ifndef NETWORKITEMEVENTCONTROLLER_H
#define NETWORKITEMEVENTCONTROLLER_H

#include "ItemEventController.h"
#include "NetworkEventController.h"

class NetworkItemEventController : public ItemEventController,
		public NetworkEventController
{
public:
	NetworkItemEventController();
};

#endif // NETWORKITEMEVENTCONTROLLER_H
