#include "ControllerFactory.h"

ControllerFactory *ControllerFactory::s_instance = 0;

ControllerFactory *ControllerFactory::Factory()
{
	if (!s_instance)
	{
		s_instance = new ControllerFactory();
	}
	return s_instance;
}

void ControllerFactory::Destroy()
{
	if (s_instance)
	{
		delete s_instance;
	}
}

Controller *ControllerFactory::createActionPlayerController()
{
	//TODO
	//check if network
	//create object
	//register to the manager
	//return
}

Controller *ControllerFactory::createEventPlayerController()
{

}

ControllerFactory::ControllerFactory()
{
}

ControllerFactory::~ControllerFactory()
{
	//TODO
}
