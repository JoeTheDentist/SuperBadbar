#ifndef BABARSTATEJUMP_H
#define BABARSTATEJUMP_H

#include "BabarState.h"

class BabarStateJump : public BabarState
{
public:
	/**
	 *	Ctor
	 *	@param context: context of the state
	 */
	BabarStateJump(Babar *context);

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

#endif // BABARSTATEJUMP_H
