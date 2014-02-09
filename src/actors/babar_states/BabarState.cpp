#include "BabarState.h"

#include "../Babar.h"
#include "BabarStateNone.h"

BabarState::BabarState (Babar *context)
{
    m_context = context;
    m_wasFiring = false;
    m_wasCrouched = false;
}

BabarState *BabarState::GetInitialState (Babar *context)
{
    return new BabarStateNone (context);
}

void BabarState::moveLeft()
{

}

void BabarState::moveRight()
{

}

void BabarState::fire()
{

}

void BabarState::protect()
{

}

Babar *BabarState::getContext()
{
    return m_context;
}

void BabarState::setAnimation()
{

}
