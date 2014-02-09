/**
 * 	@file monster_basic_weapon.cpp
 * 	@brief Implémentation de la classe Monster_basic_weapon
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include <iostream>
#include <stdint.h>
#include <stdlib.h>

#include "MonsterBasicWeapon.h"
#include "actors/Projectile.h"
#include "util/debug.h"
#include "util/globals.h"
#include "util/repertories.h"


Monster_basic_weapon::Monster_basic_weapon()
{
    PRINT_CONSTR (2, "Construction d'une Monster_basic_weapon")
    m_last_dir_h = 3;
    m_fire_frequency = 15;
    m_weapon_type = MONSTER_BASIC_WEAPON;
    m_reload_time = 0;
    m_munitions = 999999;
}

Monster_basic_weapon::~Monster_basic_weapon()
{
    PRINT_CONSTR (2, "Destruction d'un Monster_basic_weapon")
}

std::list<Projectile*> *Monster_basic_weapon::fire (Rect pos, Direction h, dmg_chan type)
{
    std::list<Projectile*> *proj_list = new std::list<Projectile*>();
    if (rand() % m_fire_frequency == 0)
    {
        proj_list->push_back (new Projectile (pos, h, (2 * h - 1) *PROJ_SPEED, 0, 1, type) );
        gSound->play_sound (FIRE_SOUNDS_R + "monster_basic_weapon.wav");
    }
    return proj_list;
}

weapon_type Monster_basic_weapon::type_of_weapon() const
{
    return MONSTER_BASIC_WEAPON;
}

void Monster_basic_weapon::add_munitions()
{

}
