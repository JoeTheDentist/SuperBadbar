/** * 	@file event_weapon.cpp * 	@brief implémentation de la classe Event * * 	@author Guillaume Bérard & Benoit Morel * 	@date decembre 2010 * */ #include <iostream>#include "../items/weapons.h"#include "event_weapon.h"#include "../sprites/babar.h"#include "../util/collisions.h"#include "../util/debug.h"#include "../util/globals.h"#include "../util/repertories.h"#include "../video/pictures_container.h"Event_weapon::Event_weapon(Babar *target, Rect pos, Pictures_container *pictures_container) : Event_item(target, pos) {	PRINT_CONSTR(3, "Construction d'un event_weapon");	m_weapon_type =  SHOTGUN;	m_can_be_destroyed = false;	std::string chemin = PIC_R + "items/heart.bmp";	m_picture = pictures_container->load_BMP(chemin.c_str());	SDL_SetColorKey(m_picture, SDL_SRCCOLORKEY, SDL_MapRGB(m_picture->format, 0, 0, 255));}Event_weapon::~Event_weapon(){	PRINT_CONSTR(3, "Destruction d'un event_weapon");}void Event_weapon::start(){	m_can_be_destroyed = true;	m_target->change_weapon(m_weapon_type);}SDL_Surface *Event_weapon::current_picture() const{	return m_picture;}