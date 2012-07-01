#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include <list>

/**
 *	Factory for the controllers.
 *	Singleton.
 */
class ControllerFactory
{
public:
	/**
	 *	Getter of the singleton instance.
	 */
	static ControllerFactory *Factory();

private:
	static ControllerFactory *s_instance;

	/**
	 *	Constructor
	 */
	ControllerFactory();
};

#endif // CONTROLLERFACTORY_H
