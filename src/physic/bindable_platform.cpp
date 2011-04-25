/**
 * 	@file bindable_platform.cpp
 * 	@brief Implementation de la classe Bindable_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <math.h>
#include "bindable_platform.h"
#include "../game/static_data.h"
#include "../video/camera.h"
#include "../video/surface.h"
#include "../actors/babar.h"
#include "../util/analyser.h"
#include "../physic/collisions_manager.h"
#include "../physic/collisions_matrix.h"
#include "../video/displayable.h"


Bindable_platform::Bindable_platform()
{
	m_can_bind = 1;
	m_babar = NULL;
}

Bindable_platform::~Bindable_platform() 
{
	PRINT_DEBUG(1, "Suppression de moving plateforme");
	if (m_babar) {
		m_babar->unbind();
	}
}

void Bindable_platform::init_bindable_platform(int posx, int posy, std::string file_name)
{
	m_pos.x = posx;
	m_pos.y = posy;

	file_name = PIC_STATICS_R + file_name;
	m_image = new Surface(file_name + ".png");
	m_pos.h = m_image->h();
	m_pos.w = m_image->w();
	Analyser analyser;
	analyser.open(file_name + ".col");	
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

void Bindable_platform::update_pos()
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

void Bindable_platform::update_speed()
{
}

void Bindable_platform::bind()
{
	PRINT_DEBUG(1, "bind");
	m_babar = gBabar;
}

void Bindable_platform::unbind()
{
	PRINT_DEBUG(1, "unbind");
	m_babar = NULL;
	m_can_bind = -3;
}

Rect Bindable_platform::speed() const
{
	return m_speed;
}

bool Bindable_platform::is_going_down()
{
	return m_speed.y > 0;
}

bool Bindable_platform::check_babar()
{
	if (m_can_bind <= 0)
		return false;
	if (m_babar != NULL)
		return false;
//~ 	if (gBabar->binded())
//~ 		return false;

	Rect babar_speed = gBabar->speed();
	Rect babar_pos = gBabar->position();
	if (babar_speed.y < m_speed.y)
		return false;
	Rect babar_rel_pos = gBabar->position();
	babar_pos.x -= m_pos.x;
	babar_pos.y -= m_pos.y;
	return Collisions_manager::is_down_coll(this->down_collision_type(babar_pos));
}

bool Bindable_platform::dead()
{
	return m_pos.y < 0 || m_pos.y >  (int)gStatic->static_data_height();
}

bool Bindable_platform::can_bind()
{
	return m_can_bind > 0;
}

#ifdef DEBUG_COLL
void Bindable_platform::display_coll(Camera *camera)
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
