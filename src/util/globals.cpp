
#include <math.h>
#include "globals.h"

Sound_engine * gSound;
Collisions_manager * gCollision;
Static_data * gStatic;
Projectiles_manager * gProj;
Events_manager * gEvent;
Babar * gBabar;


double dist(Rect A, Rect B)
{
    Rect mA = A;
    Rect mB = B;

    mA.x = mA.x+mA.w/2;
    mA.y = mA.y+mA.h/2;

    mB.x = mB.x+mB.w/2;
    mB.y = mB.y+mB.h/2;

    return sqrt( (mA.x-mB.x)*(mA.x-mB.x) + (mA.y-mB.y)*(mA.y-mB.y) );
}
