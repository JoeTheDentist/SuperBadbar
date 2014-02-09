#ifndef BABARSTATEDOUBLEJUMP_H
#define BABARSTATEDOUBLEJUMP_H

#include "BabarState.h"

class BabarStateDoubleJump : public BabarState
{
public:
    /**
     *	Ctor
     *	@param context: context of the state
     */
    BabarStateDoubleJump (Babar *context);

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

#endif // BABARSTATEDOUBLEJUMP_H
