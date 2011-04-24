/**
 * 	@file falling_platform.cpp
 * 	@brief Implementation de la classe Falling_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <math.h>
#include "falling_platform.h"
#include "../game/static_data.h"
#include "../video/camera.h"
#include "../video/surface.h"
#include "../actors/babar.h"
#include "../util/analyser.h"
#include "../physic/collisions_manager.h"
#include "../physic/collisions_matrix.h"
#include "../video/displayable.h"


Falling_platform::Falling_platform(Analyser &analyserLevel):
	Bindable_platform(),
	m_is_falling(false)
{
	std::string file_name = analyserLevel.read_string();
	int posx = analyserLevel.read_int();
	int posy = analyserLevel.read_int();
	init_bindable_platform(posx, posy, file_name);
	m_speed.x = 0;
	m_speed.y = 0;
	m_pos.h = m_image->h();
	m_pos.w = m_image->w();
}

Falling_platform::~Falling_platform() 
{
}

void Falling_platform::update_speed()
{
	if (m_is_falling) {
		m_speed.y += 1;
	}
}

void Falling_platform::bind()
{
	m_is_falling = true;
	Bindable_platform::bind();
}
