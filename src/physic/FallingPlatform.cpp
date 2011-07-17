/**
 * 	@file FallingPlatform.cpp
 * 	@brief Implementation de la classe FallingPlatform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <math.h>
#include "FallingPlatform.h"
#include "../game/StaticData.h"
#include "../video/Camera.h"
#include "../video/Surface.h"
#include "../actors/Babar.h"
#include "../util/Analyser.h"
#include "../physic/CollisionsManager.h"
#include "../physic/CollisionsMatrix.h"
#include "../video/Displayable.h"


FallingPlatform::FallingPlatform(Analyser &analyserLevel, CollisionsManager *CollisionsManager):
	BindablePlatform(),
	m_is_falling(false),
	m_counter(-1),
	m_collisions_manager(CollisionsManager),
	m_file_name(analyserLevel.read_string())
{
	int posx = analyserLevel.read_int();
	int posy = analyserLevel.read_int();
	init_bindable_platform(posx, posy, m_file_name);
	m_pos.h = m_image->h();
	m_pos.w = m_image->w();
}

FallingPlatform::FallingPlatform(int posx, int posy, std::string file_name, CollisionsManager *CollisionsManager):
	BindablePlatform(),
	m_is_falling(false),
	m_counter(-1),
	m_collisions_manager(CollisionsManager),
	m_file_name(file_name)
{
	init_bindable_platform(posx, posy, m_file_name);
	m_pos.h = m_image->h();
	m_pos.w = m_image->w();
}


FallingPlatform::~FallingPlatform()
{
}

void FallingPlatform::update_speed()
{
	m_counter--;
	if (m_counter == 0)
		begin_fall();
	if (m_is_falling) {
		m_speed.y += 3;
	}
}

void FallingPlatform::bind()
{
	BindablePlatform::bind();
	if (m_counter < 0 && !m_is_falling)
		m_counter = 10;
}

void FallingPlatform::begin_fall()
{
	m_is_falling = true;
	m_collisions_manager->addPlatform(this->duplicate(), PLATFORM_RESPAWN_TIME);
}

FallingPlatform *FallingPlatform::duplicate()
{
	return new FallingPlatform(m_pos.x, m_pos.y, m_file_name, m_collisions_manager);;
}
