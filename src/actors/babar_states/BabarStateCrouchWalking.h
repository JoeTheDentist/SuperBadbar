#ifndef BABARSTATECROUCHWALKING_H
#define BABARSTATECROUCHWALKING_H

#include "BabarState.h"

class BabarStateCrouchWalking : public BabarState
{
public:
	/**
	 *	Ctor
	 *	@param context: context of the state
	 */
	BabarStateCrouchWalking(Babar *context);

	/**
	 *	Update
	 */
	void update();

	/**
	 *	Move Up (jump & double jump)
	 */
	void moveUp();

	/**
	 *	Move Down (crouch)
	 */
	void moveDown();

	/**
	 *	Move Left
	 */
	void moveLeft();

	/**
	 *	Move Right
	 */
	void moveRight();

	/**
	 *	Fire action
	 */
	void fire();

	/**
	 *	Protect action
	 */
	void protect();
};

#endif // BABARSTATECROUCHWALKING_H
