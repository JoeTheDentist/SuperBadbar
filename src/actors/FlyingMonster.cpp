/**
 * 	@file FlyingMonster.cpp
 * 	@brief Source de la classe FlyingMonster
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "FlyingMonster.h"

#include "actors/Babar.h"
#include "util/utils.h"


FlyingMonster::FlyingMonster (std::string name, int posx, int posy) :
    Monster (name, posx, posy)
{
    PRINT_CONSTR (2, "Construction de FlyingMonster");
}

FlyingMonster::FlyingMonster (Analyser *analyserLevel) :
    Monster (analyserLevel)
{
    m_high_min = 2800;
}

FlyingMonster::~FlyingMonster()
{
    PRINT_CONSTR (2, "Destruction de FlyingMonster");
}

