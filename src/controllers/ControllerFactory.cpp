#include "ControllerFactory.h"

#include "Controller.h"
#include "PlayerKeyboardActionController.h"
#include "ControllerManager.h"

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
    return ControllerManager::GetInstance()->
           createPlayerKeyboardActionController();
}

Controller *ControllerFactory::createEventPlayerController()
{
    return 0;
}

ControllerFactory::ControllerFactory()
{
}

ControllerFactory::~ControllerFactory()
{
    //TODO
}
