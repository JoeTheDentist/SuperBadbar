/**
 * 	@file collisions_matrix.h
 * 	@brief Implémentation de la classe Collisions_matrix
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <algorithm>
#include "collisions_matrix.h"
#include "collisions_manager.h"
#include "../util/analyser.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../physic/moving_platform.h"
#include "../video/camera.h"
#include "../actors/babar.h"
#include "../util/globals.h"

Collisions_matrix::Collisions_matrix()
{
}

Collisions_matrix::Collisions_matrix(int w, int h):
	m_collisions_matrix(NULL),
	m_collisions_matrix_w(w),
	m_collisions_matrix_h(h)
{
    /*** Allocation du tableau pour les collisions ***/
    m_collisions_matrix = new uint32_t*[m_collisions_matrix_w + 1];
    for(int i = 0; i<m_collisions_matrix_w ;i++) {
        m_collisions_matrix[i] = new uint32_t[m_collisions_matrix_h + 1];
    }
    /*** Remplissage de la matrice pour les collisions ***/
    for(int i = 0;i<m_collisions_matrix_w;i++) {
        for(int j = 0;j<m_collisions_matrix_h;j++) {
            m_collisions_matrix[i][j] = NO_COLL;
        }
    }
}

Collisions_matrix::~Collisions_matrix()
{
	for(int i = 0; i < m_collisions_matrix_w;i++) {
        delete[] m_collisions_matrix[i];
    }
    delete[] m_collisions_matrix;
}

void Collisions_matrix::addStatic(int x, int y, std::string static_name)
{
	Analyser analyser_static;
	analyser_static.open((PIC_STATICS_R + static_name + COLL_EXT));
	int static_weight = analyser_static.read_int();
	int static_height = analyser_static.read_int();
	int j_min = std::max(0, y/BOX_SIZE), j_max = std::min((int)(y / BOX_SIZE + static_height), (int)m_collisions_matrix_h);
	int i_min = std::max(0, x/BOX_SIZE), i_max = std::min((int)(x / BOX_SIZE + static_weight), (int)m_collisions_matrix_w);
	for (int j = j_min ; j < j_max; j++) {
		for (int i = i_min; i < i_max; i++) {
			m_collisions_matrix[i][j] |= analyser_static.read_uint32_t();
		}
	}
	analyser_static.close();
}

uint32_t Collisions_matrix::collision(uint32_t x, uint32_t y)
{
    return m_collisions_matrix[x/BOX_SIZE][y/BOX_SIZE];
}

uint32_t Collisions_matrix::down_collision_type(Rect pos)
{
	uint32_t coll = 0;
	int i_min = std::max(pos.x,0), i_max = std::min(pos.x + pos.w, m_collisions_matrix_w * BOX_SIZE -1);
	if (pos.y + pos.h < 0 || (pos.y+pos.h)/BOX_SIZE + 1 >= m_collisions_matrix_h)
		return coll;
	for (int i = i_min ; i < i_max; i += BOX_SIZE) {
		coll |= m_collisions_matrix[i / BOX_SIZE][(pos.y + pos.h) / BOX_SIZE + 1] ;
	}
	return coll;
}

uint32_t Collisions_matrix::up_collision_type(Rect pos)
{
	uint32_t coll = 0;
	int i_min = std::max(pos.x,0), i_max = std::min(pos.x + pos.w, m_collisions_matrix_w * BOX_SIZE -1);
	for (int32_t i = i_min ; i < i_max ; i += BOX_SIZE)
		if (i / BOX_SIZE < m_collisions_matrix_w)
			coll |= m_collisions_matrix[i / BOX_SIZE][pos.y /  BOX_SIZE - 1] ;
	return coll;
}

uint32_t Collisions_matrix::right_collision_type(Rect pos)
{
	uint32_t coll = 0;
	int j_min = std::max(pos.y,0), j_max = std::min(pos.y + pos.h, m_collisions_matrix_h * BOX_SIZE - 1);
	int posx = std::min(pos.x + pos.w, m_collisions_matrix_w - BOX_SIZE);
	for (int32_t j = j_min ; j < j_max ; j += BOX_SIZE)
		if (j / BOX_SIZE < m_collisions_matrix_h)
			coll |= m_collisions_matrix[posx/ BOX_SIZE + 1][j / BOX_SIZE];
	return coll;
}

uint32_t Collisions_matrix::left_collision_type(Rect pos)
{
	uint32_t coll = 0;
	int j_min = std::max(pos.y,0), j_max = std::min(pos.y + pos.h, (m_collisions_matrix_h-1) * BOX_SIZE);
	int posx = std::max(BOX_SIZE, pos.x);
	if (pos.x < 0 || pos.x / BOX_SIZE >= m_collisions_matrix_w)
		return coll;
	for (int32_t j = j_min ; j < j_max ; j += BOX_SIZE)
		if (j / BOX_SIZE < m_collisions_matrix_h)
			coll |= m_collisions_matrix[posx / BOX_SIZE - 1][j / BOX_SIZE];
	return coll;
}

bool Collisions_matrix::up_collision(Rect pos)
{
	return Collisions_manager::is_up_coll(up_collision_type(pos));
}

bool Collisions_matrix::down_collision(Rect pos)
{
	return Collisions_manager::is_down_coll(up_collision_type(pos));
}

bool Collisions_matrix::left_collision(Rect pos)
{
	return Collisions_manager::is_right_coll(left_collision_type(pos));
}

bool Collisions_matrix::right_collision(Rect pos)
{
	return Collisions_manager::is_left_coll(right_collision_type(pos));
}

bool Collisions_matrix::double_collision(Rect pos)
{
	int i_min = std::max(pos.x,0) / BOX_SIZE;
	int i_max = std::min(pos.x + pos.w, m_collisions_matrix_w * BOX_SIZE -1) / BOX_SIZE;
	int j = (pos.y + pos.h) / BOX_SIZE;
	for (int32_t i = i_min ; i <= i_max ; i += 1) {
		if (m_collisions_matrix[i][j] == FULL_COLL) {
			return true;
		}
	}
	return false;
}

int Collisions_matrix::dim_w() {
    return m_collisions_matrix_w;
}

int Collisions_matrix::dim_h() {
    return m_collisions_matrix_h;
}

bool Collisions_matrix::can_fall(Rect pos) {
    bool ret = true;
    for (int i = -3; i<4 && ret; i++) {
        Rect p = pos;
        p.y += i*BOX_SIZE;
        ret &= !Collisions_manager::is_down_coll(down_collision_type(p));
    }
    return ret;
}

//~ Rect Collisions_matrix::position()
//~ {
//~ 	Rect rec;
//~ 	rec.x = 0;
//~ 	rec.y = 0;
//~ 	return rec;
//~ }


void Collisions_matrix::update_pos( Rect &pos, Rect &speed )
{
    int coll;
	/* cas où le sprite descend */
	for (int speed_y = speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = gCollision->get_matrix()->down_collision_type(pos);
		if (Collisions_manager::is_down_coll(coll)){
			speed_y = 0;
			speed.y = 0;
		}
		else {
			pos.y += BOX_SIZE;
			if ((unsigned int)(pos.y + pos.h) > gStatic->static_data_height())
				pos.y = gStatic->static_data_height() - pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int32_t speed_y = speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (Collisions_manager::is_up_coll(gCollision->get_matrix()->up_collision_type(pos))){
			speed_y = 0;
			speed.y = 0;
		}
		else {
			if (pos.y < 0)
				pos.y = 0;
			pos.y -= BOX_SIZE;
		}
	}
	/* cas où le sprite va à droite */
	for (int32_t speed_x = speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
			pos.y -= 	BOX_SIZE;
			if(!Collisions_manager::is_down_coll(gCollision->get_matrix()->down_collision_type(pos)))
				pos.y += BOX_SIZE;
			pos.x += BOX_SIZE;
			if (pos.x + pos.w > (int32_t)gStatic->static_data_weight())
				pos.x = gStatic->static_data_weight() - pos.w;
	}
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			pos.y -= 	BOX_SIZE;
			if(!Collisions_manager::is_down_coll(gCollision->get_matrix()->down_collision_type(pos)))
				pos.y += BOX_SIZE;
			pos.x -= BOX_SIZE;
			if (pos.x < 0)
				pos.x = 0;
	}
}


