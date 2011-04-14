/**
 * 	@file sprites.cpp
 * 	@brief Implémentation de la classe Sprite
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>

#include "sprites.h"
#include "../util/debug.h"
#include "../video/surface.h"


Sprite::Sprite()
{
    PRINT_CONSTR(3, "Construction de Sprite")
	m_phase = 0;
	m_to_delete = false;
	m_lvl = BACKGROUND;
}

Sprite::~Sprite()
{
	PRINT_CONSTR(3, "Destruction de Sprite")
}

bool Sprite::operator<(const Sprite &s) const
{
    return m_lvl < s.m_lvl;
}

Rect * Sprite::pos()
{
    return &m_pos;
}

void Sprite::set_pos(Rect pos)
{
    m_pos.x = pos.x;
    m_pos.y = pos.y;
}

void Sprite::change_anim(state_player s, direction dir, bool fire ,bool phase_rand) {}

void Sprite::change_anim(state_m s, direction dir, bool fire ,bool phase_rand) {}

void Sprite::change_text_to(std::string text, int begin_size, int end_size, int nb_pic) {}

unsigned int Sprite::phase() const
{
    return m_phase;
}

void Sprite::set_to_delete()
{
    m_to_delete = true;
}

bool Sprite::to_delete() const
{
    return m_to_delete;
}
