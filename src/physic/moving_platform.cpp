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
#include "../sprites/babar.h"
#include "../util/analyser.h"
#include "../physic/collisions_manager.h"
#include "../physic/collisions_matrix.h"
#include "../video/displayable.h"


Moving_platform::Moving_platform(Analyser &analyserLevel):
	m_speed()
{
	m_can_bind = 1;
	m_falling_platform = false;
	m_is_falling = false;
	// on parse analyserLevel
	std::string nature = analyserLevel.read_string();
	if (nature == "normal") {

	} else if (nature == "falling") {
		m_falling_platform = true;
	}
	std::string file_name;
	file_name = PIC_STATICS_R + analyserLevel.read_string();
	std::cout << "file_name : " << file_name << std::endl;
	m_image = new Surface(file_name + ".png");
	int beginx = analyserLevel.read_int();
	int beginy = analyserLevel.read_int();
	int endx = analyserLevel.read_int();
	int endy = analyserLevel.read_int();

	// on commence la construction
	m_babar = NULL;
	Analyser analyser;
	analyser.open(file_name + ".col");
	m_pos.x = beginx;
	m_pos.y = beginy;
	m_begin.x = std::min(beginx, endx);
	m_begin.y = std::min(beginy, endy);
	m_end.x = std::max(beginx, endx);
	m_end.y = std::max(beginy, endy);
	m_phase = 0;
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

	m_collisions_matrix_w = analyser.read_int();
	m_collisions_matrix_h = analyser.read_int();
	m_collisions_matrix = new unsigned int*[m_collisions_matrix_w];
	for (int i = 0; i < m_collisions_matrix_w; i++) {
		m_collisions_matrix[i] = new unsigned int[m_collisions_matrix_h];
	}
	for (int j = 0; j < m_collisions_matrix_h; j++) {
		for (int i = 0; i < m_collisions_matrix_w; i++) {
			m_collisions_matrix[i][j] = analyser.read_int();
		}
	}
	analyser.close();
}

Moving_platform::~Moving_platform() {}

void Moving_platform::update_pos()
{
	if (m_can_bind <= 0)
		m_can_bind++;
	m_phase++;
	/* descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		if (check_babar())
			gBabar->bind(this);
		m_pos.y += BOX_SIZE;
		if (m_babar)
			m_babar->check_unbind();
	}
	/* cas monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		check_babar();
		m_pos.y -= BOX_SIZE;
		if (m_babar)
			m_babar->check_unbind();
	}
	/* droite */
	for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
		check_babar();
		m_pos.x += 	BOX_SIZE;
		if (m_babar)
			m_babar->check_unbind();
	}
	/* gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
		check_babar();
		m_pos.x -= BOX_SIZE;
		if (m_babar)
			m_babar->check_unbind();
	}
}

void Moving_platform::update_speed()
{
	if (!m_is_falling) {
		if (m_pos.x < m_begin.x || m_pos.x > m_end.x ) {
			m_speed.x *= -1;
		}
		if (m_pos.y < m_begin.y || m_pos.y > m_end.y ) {
			m_speed.y *= -1;
		}
	} else {
		m_speed.y += 3;
	}
}

void Moving_platform::bind()
{
	if (can_bind()) {
		if (m_falling_platform && !m_is_falling) {
			m_is_falling = true;
			m_speed.x = 0;
			m_speed.y = 0;
		}
		PRINT_DEBUG(1, "bind");
		m_babar = gBabar;
	}
}

void Moving_platform::unbind()
{
	PRINT_DEBUG(1, "unbind");
	m_babar = NULL;
//~ 	m_can_bind = -3;
}

Rect Moving_platform::speed() const
{
	return m_speed;
}

bool Moving_platform::is_going_down()
{
	return m_speed.y > 0;
}

bool Moving_platform::check_babar()
{
	if (m_can_bind <= 0)
		return false;
	if (m_babar != NULL)
		return false;
	if (gBabar->binded())
		return false;

	Rect babar_speed = gBabar->speed();
	Rect babar_pos = gBabar->position();
	if (babar_speed.y < m_speed.y)
		return false;
	Rect babar_rel_pos = gBabar->position();
	babar_pos.x -= m_pos.x;
	babar_pos.y -= m_pos.y;
	return Collisions_manager::is_down_coll(this->down_collision_type(babar_pos));
}

bool Moving_platform::dead()
{
	return m_pos.y < 0 || m_pos.y >  (int)gStatic->static_data_height();
}

bool Moving_platform::can_bind()
{
	return m_can_bind > 0;
}

#ifdef DEBUG_COLL
void Moving_platform::display_coll(Camera *camera)
{
	Rect plop;
	for (int i = 0; i < m_collisions_matrix_w; i ++) {
		plop.x = i * BOX_SIZE + m_pos.x;
		for (int j = 0; j < m_collisions_matrix_h; j++) {
			if (m_collisions_matrix[i][j] == 4) {
				plop.y = j * BOX_SIZE + m_pos.y;
				camera->display_green_coll(plop);
			} else if (m_collisions_matrix[i][j] == 15) {
				plop.y = j*BOX_SIZE;
				camera->display_red_coll(plop);
			}
		}
	}
}
#endif
