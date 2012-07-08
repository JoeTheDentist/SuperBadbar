#ifndef KEYBOARDACTIONCONTROLLER_H
#define KEYBOARDACTIONCONTROLLER_H

#include <vector>

#include "ActionController.h"

class KeyboardActionController : virtual public ActionController
{
public:
	/**
	 *	Ctor
	 */
	KeyboardActionController();

	/**
	 *	Updates the controller.
	 *	Refresh the pressed keys.
	 */
	virtual void update();

	/**
	 *	All the keys that changed since last update
	 */
	//virtual std::vector<> keyChanged();

	/**
	 *	If the given key is pressed
	 */
	//virtual bool isPressed();
};

#endif // KEYBOARDACTIONCONTROLLER_H
