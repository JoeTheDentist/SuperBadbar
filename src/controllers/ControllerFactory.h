#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include <list>

class Controller;

/**
 *	Factory for the controllers.
 *	Singleton.
 */
class ControllerFactory
{
public:
	/**
	 *	Getter of the singleton instance
	 *	@return instance
	 */
	static ControllerFactory *Factory();

	/**
	 *	Frees the instance
	 */
	static void Destroy();

	/**
	 *	Getter of a new action controller for player
	 *	@return new controller
	 */
	Controller *createActionPlayerController();

	/**
	 *	Getter of a new event controller for player
	 *	@return new controller
	 */
	Controller *createEventPlayerController();

private:
	static ControllerFactory *s_instance;

	/**
	 *	Ctor
	 */
	ControllerFactory();

	/**
	 *	Dtor
	 */
	~ControllerFactory();
};

#endif // CONTROLLERFACTORY_H
