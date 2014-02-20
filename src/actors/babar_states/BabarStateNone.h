#ifndef BABARSTATENONE_H
#define BABARSTATENONE_H

#include "BabarState.h"

class BabarStateNone : public BabarState
{
public:
    /**
     *	Ctor
     *	@param context: context of the state
     */
    BabarStateNone (Babar *context);

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

#endif // BABARSTATENONE_H
