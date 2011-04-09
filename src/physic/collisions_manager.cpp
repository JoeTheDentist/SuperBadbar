/**
 * 	@file collisions_manager.h
 * 	@brief Implémentation de la classe Collisions_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "collisions_manager.h"
#include "stdint.h"
#include "../util/analyser.h"
#include "../util/debug.h"
#include "../util/repertories.h"
#include "../sprites/babar.h"
#include "../util/globals.h"
#include "../video/camera.h"

#include <iostream> 
#include <algorithm> 

Collisions_manager::Collisions_manager()
{
	PRINT_CONSTR(1, "Construction de Collisions_manager")
}

Collisions_manager::~Collisions_manager()
{
	for(std::list<Moving_platform *>::const_iterator it = m_moving_platforms.begin();
			it != m_moving_platforms.end(); it++) {
		delete (*it);
	}
}

void Collisions_manager::init_collisions_manager(int level)
{
	Analyser analyser;
	std::string str_lvl;
    char str[3];
    sprintf(str, "%d", level);
	str_lvl = str;
	init_collisions_manager(LEVELS_R + "level" + str_lvl + ".lvl");
}

void Collisions_manager::init_collisions_manager(std::string level_name)
{
	Analyser analyser;
	analyser.open(level_name);
	analyser.find_string("#Level_dimensions#");
	int w = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
	int h = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
	m_matrix = new Collisions_matrix(w, h);
	init_statics(analyser);
	init_moving_plateforms(analyser);
	analyser.close();
}

void Collisions_manager::init_statics(Analyser &analyser)
{
	// ATTENTION: ici on charge les collisions des statics, mais pas leurs images
    analyser.find_string("#Statics#");
	analyser.read_int();
	std::string static_name = analyser.read_string();
    while(static_name[0]!='!') {
		int x = analyser.read_int();
		int y = analyser.read_int();
		analyser.read_int();
		m_matrix->addStatic(x, y, static_name);
		static_name = analyser.read_string();
	}
}

void Collisions_manager::init_moving_plateforms(Analyser &analyser)
{
    analyser.find_string("#Platforms#");

    int platforms_number = analyser.read_int();
	for (int i = 0; i  < platforms_number; i++) {
        m_moving_platforms.push_back(new Moving_platform(analyser));
    }
}

bool Collisions_manager::check_collision(Rect A, Rect B)
{
	uint16_t A_right = A.x + A.w;
	uint16_t B_right = B.x + B.w;
	uint16_t A_bottom = A.y + A.h;
	uint16_t B_bottom = B.y + B.h;
	bool A_in_B = ((B.x < A.x && A.x < B_right) || (B.x < A_right && A_right < B_right )) && ((B.y < A.y && A.y < B_bottom) || (B.y < A_bottom && A_bottom < B_bottom ));
	bool B_in_A = ((A.x < B.x && B.x < A_right) || (A.x < B_right && B_right < A_right )) && ((A.y < B.y && B.y < A_bottom) || (A.y < B_bottom && B_bottom < A_bottom ));
	return A_in_B || B_in_A;
}

void Collisions_manager::display_platforms(Camera * const camera) const
{
	for(std::list<Moving_platform *>::const_iterator it = m_moving_platforms.begin();
			it != m_moving_platforms.end(); it++) {
		camera->display((*it));
		#ifdef DEBUG_COLL
		(*it)->display_coll(camera);
		#endif
	}

}

void Collisions_manager::update_platforms_pos()
{
	for(std::list<Moving_platform *>::const_iterator it = m_moving_platforms.begin();
			it != m_moving_platforms.end(); it++) {
		(*it)->update_pos();
	}
}

void Collisions_manager::update_platforms_speed()
{
	for(std::list<Moving_platform *>::const_iterator it = m_moving_platforms.begin();
			it != m_moving_platforms.end(); it++) {
		(*it)->update_speed();
	}
}

void Collisions_manager::update_babar_platforms()
{
	for(std::list<Moving_platform *>::const_iterator it = m_moving_platforms.begin();
			it != m_moving_platforms.end(); it++) {
		if((*it)->check_babar()) {
			(*it)->bind();
			gBabar->bind((*it));
		}
	}
}

void Collisions_manager::update_dead_platforms()
{
	for(std::list<Moving_platform *>::iterator it = m_moving_platforms.begin();
			it != m_moving_platforms.end();) {
		if ((*it)->dead()) {
			delete (*it);
			it = m_moving_platforms.erase(it);
		} else {
			it++;
		}
	}
}




bool Collisions_manager::is_up_coll(uint32_t coll_number)
{
	return ((coll_number & 0x8) == 0x8);
}

bool Collisions_manager::is_down_coll(uint32_t coll_number)
{
	return ((coll_number & 0x4) == 0x4);
}

bool Collisions_manager::is_left_coll(uint32_t coll_number)
{
	return ((coll_number & 0x2) == 0x2);
}

bool Collisions_manager::is_right_coll(uint32_t coll_number)
{
	return ((coll_number & 0x1) == 0x1);
}

#ifdef DEBUG_COLL
void Collisions_manager::display_coll(Camera *camera)
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
