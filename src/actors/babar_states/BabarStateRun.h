#ifndef BABARSTATERUN_H
#define BABARSTATERUN_H

#include "BabarState.h"

class BabarStateRun : public BabarState
{
public:
    /**
     *	Ctor
     *	@param context: context of the state
     */
    BabarStateRun (Babar *context);

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

#endif // BABARSTATERUN_H
