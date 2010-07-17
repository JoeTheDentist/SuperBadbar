
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "animations.h"
#include "globals.h"
#include "events.h"


/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	m_nb_animations = 1;
	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.w = 0;
	m_pos.h = 0;
	m_speed.x = 0;
	m_speed.y = 0;
	m_cache = true;
	m_horizontal = MIDDLE_h;
	m_vertical = MIDDLE_v;
	m_state = STATIC;
	m_phase = 0;
	m_animations = new Animation*[m_nb_animations];
}

Sprite::~Sprite()
{
    for(int i = 0; i<m_nb_animations; i++) {
        delete m_animations[i];
    }
    delete[] m_animations;
}

void Sprite::update_pos()
{
	m_pos.x += m_speed.x;
	m_pos.y += m_speed.y;
	m_phase++;
}

SDL_Surface *Sprite::current_picture()
{
    /* On change d'image tous les ANIMATION_SPEED cycles */
    if (m_phase%ANIMATION_SPEED==0) {
        m_animations[/*m_state*/0]->next_pic();
    }
	if (m_animations != NULL)
		return m_animations[/*m_state*/0]->current_pic();
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
	m_nb_animations = 1;

	/* Déclarations des animtions de Babar, avec chargement des images etc etc */
	SDL_Surface **array_walking;
    array_walking = new SDL_Surface*[2];

    array_walking[0] = SDL_LoadBMP("../pic/babar_fixe_droite.bmp");
    array_walking[1] = SDL_LoadBMP("../pic/babar_marche_droite.bmp");
    SDL_SetColorKey(array_walking[0], SDL_SRCCOLORKEY, SDL_MapRGB(array_walking[0]->format, 0, 0, 255));
	SDL_SetColorKey(array_walking[1], SDL_SRCCOLORKEY, SDL_MapRGB(array_walking[1]->format, 0, 0, 255));

    Animation *walking;
    walking = new Animation(2, array_walking);
    m_animations[0] = walking;
}

Babar::~Babar()
{

}

void Babar::update_speed()
{
    if (m_state == JUMP) {
        m_speed.y += GRAVITE;

        m_speed.x = 0;                      /* Pour pouvoir se diriger en l'air */
        if (Events_stat.key_down(k_left))
            m_speed.x -= BABAR_SPEED;
        if (Events_stat.key_down(k_right))
            m_speed.x += BABAR_SPEED;
    }
    else {
        m_speed.x = 0;
        if (Events_stat.key_down(k_left))
            m_speed.x -= BABAR_SPEED;
        if (Events_stat.key_down(k_right))
            m_speed.x += BABAR_SPEED;
        m_speed.y = 0;
        if (Events_stat.key_down(k_up))
            m_speed.y -= BABAR_SPEED;
        if (Events_stat.key_down(k_down))
            m_speed.y += BABAR_SPEED;
    }

}

void Babar::update_state()
{
    m_horizontal = MIDDLE_h;
    m_vertical = MIDDLE_v;
	if (Events_stat.key_down(k_left))
		m_horizontal = LEFT;
	if (Events_stat.key_down(k_right))
		m_horizontal = RIGHT;
	if (Events_stat.key_down(k_up))
		m_vertical = UP;
	if (Events_stat.key_down(k_down))
		m_vertical = DOWN;
    if (Events_stat.key_down(k_jump)&&(m_state!=JUMP)) {    /* Début du saut */
        m_state = JUMP;
        m_speed.y = -5*BABAR_SPEED;
        m_speed.x = m_horizontal*BABAR_SPEED;
    }
    if ((m_pos.y+m_pos.h)>bottom)
        m_state = STATIC;
}


/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster()
{
}

Monster::Monster(uint32_t type, SDL_Rect pos, uint32_t area)
{
    SDL_Surface **array_static;
    array_static = new SDL_Surface*[1];

	m_pos = pos;
	m_area = area;
	m_type = type;
	m_nb_animations = 1;

	array_static[0] = SDL_LoadBMP("../pic/blob.bmp");
    SDL_SetColorKey(array_static[0], SDL_SRCCOLORKEY, SDL_MapRGB(array_static[0]->format, 0, 0, 255));

    Animation *a_static;
    a_static = new Animation(1, array_static);
    m_animations[0] = a_static;
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
