/**
 * 	@file ChainedPlatform.cpp
 * 	@brief Implementation de la classe ChainedPlatform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mai 2011
 *
 */

#include <iostream>
#include <math.h>
#include "ChainedPlatform.h"
#include "../game/StaticData.h"
#include "../video/Camera.h"
#include "../video/Surface.h"
#include "../actors/Babar.h"
#include "../util/Analyser.h"
#include "../physic/CollisionsManager.h"
#include "../physic/CollisionsMatrix.h"
#include "../video/Displayable.h"


ChainedPlatform::ChainedPlatform(Analyser &analyserLevel):
	BindablePlatform()
{
	std::string file_name = analyserLevel.read_string();
	int beginx = analyserLevel.read_int();
	int beginy = analyserLevel.read_int();
	int endx = analyserLevel.read_int();
	int endy = analyserLevel.read_int();
	init_bindable_platform(beginx, beginy, file_name);
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

ChainedPlatform::~ChainedPlatform()
{
}

void ChainedPlatform::update_speed()
{
//~ 	if (m_pos.x < m_begin.x || m_pos.x > m_end.x ) {
//~ 		m_speed.x *= -1;
//~ 	}
//~ 	if (m_pos.y < m_begin.y || m_pos.y > m_end.y ) {
//~ 		m_speed.y *= -1;
//~ 	}
}

