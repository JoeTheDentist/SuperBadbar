#ifndef BABARSTATECROUCHNONE_H
#define BABARSTATECROUCHNONE_H

#include "BabarState.h"

class BabarStateCrouchNone : public BabarState
{
public:
	/**
	 *	Ctor
	 *	@param context: context of the state
	 */
	BabarStateCrouchNone(Babar *context);

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

#endif // BABARSTATECROUCHNONE_H
