#include "BabarStateNone.h"

#include "../Babar.h"
#include "sprites/SpriteGrid.h"

BabarStateNone::BabarStateNone (Babar *context)
    : BabarState (context)
{
    if (getContext()->getDirection() == LEFT)
    {
        getContext()->getSprite()->setPictures (3);
    }
    else
    {
        getContext()->getSprite()->setPictures (0);
    }
}

void BabarStateNone::update()
{

}

void BabarStateNone::moveUp()
{

}

void BabarStateNone::moveDown()
{

}

void BabarStateNone::moveLeft()
{

}

void BabarStateNone::moveRight()
{

}

void BabarStateNone::fire()
{

}

void BabarStateNone::protect()
{

}
