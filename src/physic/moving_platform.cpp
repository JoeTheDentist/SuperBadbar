/**
 * 	@file moving_platform.cpp
 * 	@brief Implementation de la classe Moving_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <math.h>
#include "moving_platform.h"
#include "../game/static_data.h"
#include "../video/camera.h"
#include "../video/surface.h"
#include "../actors/babar.h"
#include "../util/analyser.h"
#include "../physic/collisions_manager.h"
#include "../physic/collisions_matrix.h"
#include "../video/displayable.h"


Moving_platform::Moving_platform(Analyser &analyserLevel):
	Bindable_platform()
{
	std::string file_name = analyserLevel.read_string();
	std::cout << "file_name : " << file_name << std::endl;
	int beginx = analyserLevel.read_int();
	int beginy = analyserLevel.read_int();
	int endx = analyserLevel.read_int();
	int endy = analyserLevel.read_int();
	init_bindable_platform(beginx, beginy, file_name);
	m_begin.x = std::min(beginx, endx);
	m_begin.y = std::min(beginy, endy);
	m_end.x = std::max(beginx, endx);
	m_end.y = std::max(beginy, endy);
	m_pos.h = m_image->h();
	m_pos.w = m_image->w();

	m_speed.x = beginx-endx;
	m_speed.y = beginy-endy;
	/*Normalisation du vecteur vitesse*/
	double norme = sqrt(m_speed.x*m_speed.x+m_speed.y*m_speed.y);
	if (norme != 0) {
		m_speed.x = (m_speed.x*5)/norme;
		m_speed.y = (m_speed.y*5)/norme;
	}
}

Moving_platform::~Moving_platform() 
{
}

void Moving_platform::update_speed()
{
	if (m_pos.x < m_begin.x || m_pos.x > m_end.x ) {
		m_speed.x *= -1;
	}
	if (m_pos.y < m_begin.y || m_pos.y > m_end.y ) {
		m_speed.y *= -1;
	}
}

