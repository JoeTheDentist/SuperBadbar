/**
 * 	@file CollisionsMatrix.h
 * 	@brief Implémentation de la classe CollisionsMatrix
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <algorithm>
#include "CollisionsMatrix.h"
#include "CollisionsManager.h"
#include "util/Analyser.h"
#include "util/debug.h"
#include "util/repertories.h"
#include "physic/MovingPlatform.h"
#include "video/Camera.h"
#include "actors/Babar.h"
#include "util/globals.h"

CollisionsMatrix::CollisionsMatrix()
{
}

CollisionsMatrix::CollisionsMatrix(int w, int h):
	m_collisions_matrix(NULL),
	m_collisions_matrix_w(w),
	m_collisions_matrix_h(h)
{
    /*** Allocation du tableau pour les collisions ***/
    m_collisions_matrix = new unsigned int*[m_collisions_matrix_w + 1];
    for(int i = 0; i<m_collisions_matrix_w ;i++) {
        m_collisions_matrix[i] = new unsigned int[m_collisions_matrix_h + 1];
    }
    /*** Remplissage de la matrice pour les collisions ***/
    for(int i = 0;i<m_collisions_matrix_w;i++) {
        for(int j = 0;j<m_collisions_matrix_h;j++) {
            m_collisions_matrix[i][j] = NO_COLL;
        }
    }
}

CollisionsMatrix::~CollisionsMatrix()
{
	for(int i = 0; i < m_collisions_matrix_w;i++) {
        delete[] m_collisions_matrix[i];
    }
    delete[] m_collisions_matrix;
}

void CollisionsMatrix::addStatic(int x, int y, int varCol, std::string static_name)
{
	Analyser analyser_static;
	analyser_static.open((PIC_STATICS_R + static_name + COLL_EXT));
	int static_width = analyser_static.read_int();
	int static_height = analyser_static.read_int();
	int j_min = y/BOX_SIZE, j_max = int(y / BOX_SIZE + static_height);
	int i_min = x/BOX_SIZE, i_max = int(x / BOX_SIZE + static_width);
	for (int j = j_min ; j < j_max; j++) {
		for (int i = i_min; i < i_max; i++) {
			if (i_max >= m_collisions_matrix_w || j_max >= m_collisions_matrix_h || i < 0 || j < 0) {
				analyser_static.read_unsigned_int();
			} else {
				unsigned int coll = analyser_static.read_unsigned_int();
				if (coll >> 31 == 0) {
					m_collisions_matrix[i][j] |= coll;
				} else {
					m_collisions_matrix[i][j] |= varCol;
				}
			}
		}
	}
	analyser_static.close();
}

unsigned int CollisionsMatrix::collision(unsigned int x, unsigned int y)
{
    return m_collisions_matrix[x/BOX_SIZE][y/BOX_SIZE];
}

unsigned int CollisionsMatrix::down_collision_type(Rect pos)
{
	unsigned int coll = 0;
	int i_min = std::max(pos.x,0), i_max = std::min(pos.x + pos.w, m_collisions_matrix_w * BOX_SIZE -1);
	if (pos.y + pos.h < 0 || (pos.y+pos.h)/BOX_SIZE + 1 >= m_collisions_matrix_h)
		return coll;
	for (int i = i_min ; i < i_max; i += BOX_SIZE) {
		coll |= m_collisions_matrix[i / BOX_SIZE][(pos.y + pos.h) / BOX_SIZE + 1] ;
	}
	return coll;
}

unsigned int CollisionsMatrix::up_collision_type(Rect pos)
{
	unsigned int coll = 0;
	int i_min = std::max(pos.x,0), i_max = std::min(pos.x + pos.w, m_collisions_matrix_w * BOX_SIZE -1);
	for (int i = i_min ; i < i_max ; i += BOX_SIZE)
		if (i / BOX_SIZE < m_collisions_matrix_w)
			coll |= m_collisions_matrix[i / BOX_SIZE][pos.y /  BOX_SIZE - 1] ;
	return coll;
}

unsigned int CollisionsMatrix::right_collision_type(Rect pos)
{
	unsigned int coll = 0;
	int j_min = std::max(pos.y,0), j_max = std::min(pos.y + pos.h, m_collisions_matrix_h * BOX_SIZE);
	int posx = std::min(pos.x + pos.w, m_collisions_matrix_w * BOX_SIZE - 3 *BOX_SIZE);
	for (int j = j_min ; j < j_max ; j += BOX_SIZE)
		if (j / BOX_SIZE < m_collisions_matrix_h)
			coll |= m_collisions_matrix[posx/ BOX_SIZE + 1][j / BOX_SIZE];
	return coll;
}

unsigned int CollisionsMatrix::left_collision_type(Rect pos)
{
	unsigned int coll = 0;
	int j_min = std::max(pos.y,0), j_max = std::min(pos.y + pos.h, (m_collisions_matrix_h-1) * BOX_SIZE);
	int posx = std::max(BOX_SIZE, pos.x);
	if (pos.x < 0 || pos.x / BOX_SIZE >= m_collisions_matrix_w)
		return coll;
	for (int j = j_min ; j < j_max ; j += BOX_SIZE)
		if (j / BOX_SIZE < m_collisions_matrix_h)
			coll |= m_collisions_matrix[posx / BOX_SIZE - 1][j / BOX_SIZE];
	return coll;
}

bool CollisionsMatrix::up_collision(Rect pos)
{
	return CollisionsManager::is_up_coll(up_collision_type(pos));
}

bool CollisionsMatrix::down_collision(Rect pos)
{
	return CollisionsManager::is_down_coll(up_collision_type(pos));
}

bool CollisionsMatrix::left_collision(Rect pos)
{
	return CollisionsManager::is_right_coll(left_collision_type(pos));
}

bool CollisionsMatrix::right_collision(Rect pos)
{
	return CollisionsManager::is_left_coll(right_collision_type(pos));
}

bool CollisionsMatrix::double_collision(Rect pos)
{
	int i_min = std::max(pos.x,0) / BOX_SIZE;
	int i_max = std::min(pos.x + pos.w, m_collisions_matrix_w * BOX_SIZE -1) / BOX_SIZE;
	int j = (pos.y + pos.h) / BOX_SIZE;
	for (int i = i_min ; i <= i_max ; i += 1) {
		if (m_collisions_matrix[i][j] == FULL_COLL) {
			return true;
		}
	}
	return false;
}

int CollisionsMatrix::dim_w() {
    return m_collisions_matrix_w;
}

int CollisionsMatrix::dim_h() {
    return m_collisions_matrix_h;
}

bool CollisionsMatrix::can_fall(Rect pos) {
    bool ret = true;
    for (int i = -3; i<4 && ret; i++) {
        Rect p = pos;
        p.y += i*BOX_SIZE;
        ret &= !CollisionsManager::is_down_coll(down_collision_type(p));
    }
    return ret;
}

void CollisionsMatrix::update_pos( Rect &pos, Rect &speed )
{
    int coll;
	/* cas où le sprite descend */
	for (int speed_y = speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = gCollision->get_matrix()->down_collision_type(pos);
		if (CollisionsManager::is_down_coll(coll)){
			speed_y = 0;
			speed.y = 0;
		}
		else {
			pos.y += BOX_SIZE;
			if ((unsigned int)(pos.y + pos.h) > gStatic->StaticData_height())
				pos.y = gStatic->StaticData_height() - pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int speed_y = speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (CollisionsManager::is_up_coll(gCollision->get_matrix()->up_collision_type(pos))){
			speed_y = 0;
			speed.y = 0;
		}
		else {
			if (pos.y < 0)
				pos.y = 0;
			pos.y -= BOX_SIZE;
		}
	}
	/* cas où le sprite va �  droite */
	for (int speed_x = speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
			pos.y -= 	BOX_SIZE;
			if(!CollisionsManager::is_down_coll(gCollision->get_matrix()->down_collision_type(pos)))
				pos.y += BOX_SIZE;
			pos.x += BOX_SIZE;
			if (pos.x + pos.w > (int)gStatic->StaticData_width())
				pos.x = gStatic->StaticData_width() - pos.w;
	}
	/* cas où le sprite va �  gauche */
	for (int speed_x = speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			pos.y -= 	BOX_SIZE;
			if(!CollisionsManager::is_down_coll(gCollision->get_matrix()->down_collision_type(pos)))
				pos.y += BOX_SIZE;
			pos.x -= BOX_SIZE;
			if (pos.x < 0)
				pos.x = 0;
	}
}


#ifdef DEBUG_COLL
void CollisionsMatrix::display_coll(Camera *camera)
{
	Rect plop;
	for (int i = 0; i < m_collisions_matrix_w; i ++) {
		plop.x = i * BOX_SIZE;
		for (int j = 0; j < m_collisions_matrix_h; j++) {
			if (m_collisions_matrix[i][j] == 4) {
				plop.y = j * BOX_SIZE;
				camera->display_green_coll(plop);
			} else if (m_collisions_matrix[i][j] == 15) {
				plop.y = j*BOX_SIZE;
				camera->display_red_coll(plop);
			}
		}
	}
}
#endif

