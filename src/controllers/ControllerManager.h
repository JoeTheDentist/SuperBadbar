#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <list>

class Controller;
class MenuKeyboardActionController;
class NetworkMenuActionController;
class PlayerKeyboardActionController;
class NetworkLocalPlayerActionController;
class NetworkRemotePlayerActionController;

/**
 *	Manager for all controllers
 *	Singleton
 */
class ControllerManager
{
public:
	/**
	 *	Getter
	 *	@return instance
	 */
	static ControllerManager *GetInstance();

	/**
	 *	Frees the instance
	 */
	static void Destroy();

	/**
	 *	Updates all controllers
	 */
	void update();

	/**
	 *	Create a new controller
	 */
	MenuKeyboardActionController *createMenuKeyboardActionController();

	/**
	 *	Create a new controller
	 */
	NetworkMenuActionController *createNetworkMenuActionController();

	/**
	 *	Create a new controller
	 */
	PlayerKeyboardActionController *createPlayerKeyboardActionController();

	/**
	 *	Create a new controller
	 */
	NetworkLocalPlayerActionController *
	createNetworkLocalPlayerActionController();

	/**
	 *	Create a new controller
	 */
	NetworkRemotePlayerActionController *
	createNetworkRemotePlayerActionController();

private:
	static ControllerManager *s_instance;
	std::list<Controller*> m_controllers;

	/**
	 *	Ctor
	 */
	ControllerManager();

	/**
	 *	Dtor
	 */
	~ControllerManager();
};

#endif // CONTROLLERMANAGER_H
