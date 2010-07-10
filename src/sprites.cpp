
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "globals.h"
#include "events.h"


/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	m_nb_pictures = 1;
	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.w = 0;
	m_pos.h = 0;
	m_speed.x = 0;
	m_speed.y = 0;
	m_cache = true;
	m_direction = DROITE;
	m_phase = 0;
	m_picture = new SDL_Surface*[m_nb_pictures];
}

Sprite::~Sprite()
{
	delete[] m_picture;
}

void Sprite::update_pos()
{
	m_pos.x += m_speed.x;
	m_pos.y += m_speed.y;
	m_phase++;
}

SDL_Surface *Sprite::current_picture()
{
	if (m_picture != NULL)
		return m_picture[0];
	else
		return NULL;
}

SDL_Rect Sprite::position()
{
	return m_pos;
}

uint32_t Sprite::position_x()
{
	return m_pos.x;
}

uint32_t Sprite::position_y()
{
	return m_pos.y;
}


/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar()
{
	m_pos.w = 163;
	m_pos.h = 234;
	m_picture[0] = SDL_LoadBMP("../pic/babar_fixe_droite.bmp");
	SDL_SetColorKey(m_picture[0], SDL_SRCCOLORKEY, SDL_MapRGB(m_picture[0]->format, 0, 0, 255)); /* Transparence bleu 255 */
}

Babar::~Babar()
{

}

void Babar::update_speed()
{
	m_speed.x = 0;
	if (Events_stat.key_down(k_left))
		m_speed.x -= VITESSE_BABAR;
	if (Events_stat.key_down(k_right))
		m_speed.x += VITESSE_BABAR;
	m_speed.y = 0;
	if (Events_stat.key_down(k_up))
		m_speed.y -= VITESSE_BABAR;
	if (Events_stat.key_down(k_down))
		m_speed.y += VITESSE_BABAR;
}


/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster()
{
}

Monster::Monster(uint32_t type, SDL_Rect pos, uint32_t area)
{
	m_pos = pos;
	m_area = area;
	m_type = type;
	m_picture[0] = SDL_LoadBMP("../pic/blob.bmp");
}

Monster::~Monster()
{
}

void Monster::update_speed()
{
	if (m_phase % m_area < m_area / 2)
		m_speed.x = 5;
	else
		m_speed.x = -5;
}
