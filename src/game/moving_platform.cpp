/**
 * 	@file moving_platform.cpp
 * 	@brief Implementation de la classe Moving_platform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#include <iostream>
#include "moving_platform.h"
#include "../video/surface.h"
#include "../sprites/babar.h"
#include "../util/analyser.h"
#include "../util/debug.h"
#include "../game/collisions_manager.h"

Moving_platform::Moving_platform(std::string file_name)
{
	m_surface = new Surface(file_name + ".png");
	m_babar = NULL;
	Analyser analyser;
	analyser.open(file_name + ".col");
	m_pos.x = 900;
	m_pos.y = 1000;
	m_phase = 0;
	m_pos.h = m_surface->h();
	m_pos.w = m_surface->w();
	m_speed.x = 5;
	m_speed.y = 5;
	coll_size_w = analyser.read_int();
	coll_size_h = analyser.read_int();
	m_collisions_matrix = new unsigned int*[coll_size_w];
	for (int i = 0; i < coll_size_w; i++) {
		m_collisions_matrix[i] = new unsigned int[coll_size_h];
	}
	for (int j = 0; j < coll_size_h; j++) {
		for (int i = 0; i < coll_size_w; i++) {
			m_collisions_matrix[i][j] = analyser.read_int();
		}
	}
	analyser.close();
}

Moving_platform::~Moving_platform()
{
	for (int i = 0; i < coll_size_w; i++) {
		delete[] m_collisions_matrix[i];
	}	
	delete[] m_collisions_matrix;
	delete m_surface;
}

void Moving_platform::update_pos(Babar *babar)
{
	m_phase++;
	/* descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		check_babar(babar);
		m_pos.y += BOX_SIZE;
	}
	/* cas monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		check_babar(babar);
		m_pos.y -= BOX_SIZE;
	}
	/* droite */
	for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
		check_babar(babar);
		m_pos.x += 	BOX_SIZE;
	}
	/* gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
		check_babar(babar);
		m_pos.x -= BOX_SIZE;
	}

	
}

void Moving_platform::update_speed()
{
	if (m_phase % 30 == 0) {
		m_speed.x = -m_speed.x;
		m_speed.y = -m_speed.y;
	}
}

void Moving_platform::bind(Babar *babar)
{
	m_babar = babar;
}

void Moving_platform::unbind()
{
	m_babar = NULL;
}

Surface *Moving_platform::current_picture() const
{
	return m_surface;
}

Rect Moving_platform::position() const
{
	return m_pos;
}

Rect Moving_platform::speed() const
{
	return m_speed;
}


bool Moving_platform::check_babar(Babar *babar)
{
	Rect babar_speed = babar->speed();
	Rect babar_pos = babar->position();
	if (babar_speed.y < m_speed.y) 
		return false;
	int j = (babar_pos.y + babar_pos.h - m_pos.y) / BOX_SIZE + 1;
	if (j < 0 || j > coll_size_h)
		return false;
	int i_deb = (babar_pos.x - m_pos.x) / BOX_SIZE;
	int i_max = (babar_pos.x + babar_pos.w - m_pos.x) / BOX_SIZE;
	if (i_deb < 0)
		i_deb = 0;
	if (i_max > coll_size_w)
		i_max = coll_size_w;
	for (int i = i_deb; i < i_max; i++)
		if (Collisions_manager::is_down_coll(m_collisions_matrix[i][j])) {
			PRINT_DEBUG(1, "LIAISON %d %d", i, j);
			return true;
		}
	return false;
}
