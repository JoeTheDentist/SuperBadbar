/**
 * 	@file RocketLauncher.cpp
 * 	@brief Implementation de la classe RocketLauncher
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <stdint.h>

#include "RocketLauncher.h"
#include "util/debug.h"
#include <actors/Rocket.h>
#include "actors/Projectile.h"
#include "util/globals.h"
#include "util/repertories.h"


RocketLauncher::RocketLauncher()
{
    PRINT_CONSTR (2, "Construction d'une RocketLauncher")
    m_last_dir_h = 3;
    m_weapon_type = ROCKET_LAUNCHER;
    m_reload_time = RELOAD_ROCKET_LAUNCHER;
    m_munitions = MUN_ROCKET_LAUNCHER;
}

RocketLauncher::~RocketLauncher()
{
    PRINT_CONSTR (2, "Destruction d'un RocketLauncher")
}

std::list<Projectile*> *RocketLauncher::fire (Rect pos, Direction h, dmg_chan type)
{
    std::list<Projectile*> *proj_list = new std::list<Projectile*>();
    Projectile * r = new Rocket (pos, h, (2 * h - 1) *PROJ_SPEED, 0, ROCKET_DAMAGE);
    r->set_chan (type);
    proj_list->push_back (r);
    m_munitions--;
    gSound->play_sound (FIRE_SOUNDS_R + "rocket.wav");
    return proj_list;
}


weapon_type RocketLauncher::type_of_weapon() const
{
    return m_weapon_type;
}


void RocketLauncher::add_munitions()
{
    m_munitions += m_munitions;
    if (m_munitions > m_munitions)
        m_munitions = m_munitions;
}
