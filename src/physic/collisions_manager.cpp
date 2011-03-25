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
#include "../video/camera.h"
#include "../sprites/babar.h"
#include "../util/globals.h"

Collisions_manager::Collisions_manager():
	m_moving_platforms()
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
	m_collisions_matrix_w = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
	m_collisions_matrix_h = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
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
	init_statics(analyser);
	init_moving_plateforms(analyser);
	analyser.close();
}

void Collisions_manager::init_statics(Analyser &analyser)
{
	// ATTENTION: ici on charge les collisions des statics, mais pas leurs images
    analyser.find_string("#Statics#");
	analyser.read_int();
	std::string static_pic_rep = PIC_STATICS_R;
	std::string static_name = analyser.read_string();
	Analyser analyser_static;
	uint32_t static_weight, static_height;
    while(static_name[0]!='!') {
		int x = analyser.read_int();
		int y = analyser.read_int();
		analyser.read_int();
		analyser_static.open((static_pic_rep + static_name + COLL_EXT));
		static_weight = analyser_static.read_int();
		static_height = analyser_static.read_int();
		for (uint32_t j = y / BOX_SIZE ; j < y / BOX_SIZE + static_height; j++) {
			for (uint32_t i = x / BOX_SIZE; i < x / BOX_SIZE + static_weight; i++) {
				m_collisions_matrix[i][j] |= analyser_static.read_uint32_t();
			}
		}
		analyser_static.close();
		static_name = analyser.read_string();
	}
}

void Collisions_manager::init_moving_plateforms(Analyser &analyser)
{
    analyser.find_string("#Plateforms#");

    analyser.read_int();
	std::string plateform_name = analyser.read_string();
	Rect pos_begin, pos_end;
	while(plateform_name[0]!='!') {
		pos_begin.x = analyser.read_int();
		pos_begin.y = analyser.read_int();
		pos_end.x = analyser.read_int();
		pos_end.y = analyser.read_int();
        m_moving_platforms.push_back(new Moving_platform(PIC_STATICS_R + plateform_name, pos_begin.x, pos_begin.y, pos_end.x, pos_end.y));
		plateform_name = analyser.read_string();
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

