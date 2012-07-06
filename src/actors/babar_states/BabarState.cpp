#include "BabarState.h"

#include "../Babar.h"
#include "BabarStateNone.h"

BabarState::BabarState(Babar *context)
{
}

BabarState *BabarState::GetInitialState(Babar *context)
{
	return new BabarStateNone(context);
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
