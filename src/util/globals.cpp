
#include <math.h>
#include "globals.h"

Sound_engine * gSound = NULL;
Collisions_manager * gCollision = NULL;
Static_data * gStatic = NULL;
Projectiles_manager * gProj = NULL;
Events_manager * gEvent = NULL;
Babar * gBabar = NULL;
Animation_engine * gAnims = NULL;
Graphic_engine *gGraphics = NULL;
Game_engine *gGame_engine = NULL;

 
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
