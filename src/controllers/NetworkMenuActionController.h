#ifndef NETWORKMENUACTIONCONTROLLER_H
#define NETWORKMENUACTIONCONTROLLER_H

#include "MenuKeyboardActionController.h"
#include "NetworkActionController.h"

class NetworkMenuActionController : public MenuKeyboardActionController,
		public NetworkActionController
{
public:
	NetworkMenuActionController();
};

#endif // NETWORKMENUACTIONCONTROLLER_H
