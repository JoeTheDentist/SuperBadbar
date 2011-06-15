#include <stdlib.h>
#include "elmar_machine_gun.h"
#include "../actors/elmar_tile.h"

Elmar_machine_gun::Elmar_machine_gun()
{
	PRINT_CONSTR(2, "Construction d'un Elmar_machine_gun")
	m_last_dir_h = 3;
    m_weapon_type = ELMAR_MACHINE_GUN;
	m_reload_time = RELOAD_MACHINEGUN;
	m_munitions = MUN_ELMAR_MACHINE_GUN;

}

Elmar_machine_gun::~Elmar_machine_gun()
{
	PRINT_CONSTR(2, "Destruction d'un Elmar_machine_gun")
}

std::list<Projectile*> *Elmar_machine_gun::fire(Rect pos, direction h, dmg_chan type)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	if (m_munitions >= 0) {
		int dir_h = (2*h-1)*PROJ_SPEED;
		Rect other_pos = pos;
		other_pos.y +=10*(rand()%5-2);
		other_pos.x +=(2*h-1)*40;
		proj_list->push_back(new Elmar_tile(other_pos, h, dir_h, 0,1, type));
		proj_list->push_back(new Elmar_tile(pos, h, dir_h, 0,1, type));
		m_munitions -= 2;
	}
	gSound->play_sound(FIRE_SOUNDS_R + "gun.wav");
	return proj_list;
}


weapon_type Elmar_machine_gun::type_of_weapon() const
{
	return ELMAR_MACHINE_GUN;
}


void Elmar_machine_gun::add_munitions()
{
	m_munitions += MUN_ELMAR_MACHINE_GUN;
	if (m_munitions += MUN_ELMAR_MACHINE_GUN * 2)
		m_munitions = MUN_ELMAR_MACHINE_GUN * 2;

}
