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
#include "../util/globals.h"
#include "../util/debug.h"

Collisions_manager::Collisions_manager() {
	PRINT_CONSTR(1, "Construction de Collisions_manager")
}

Collisions_manager::~Collisions_manager() {
	for(uint32_t i = 0; i < m_collisions_matrix_w;i++) {
        delete[] m_collisions_matrix[i];
    }
    delete[] m_collisions_matrix;
}



void Collisions_manager::init_collisions_manager(int level) {
	Analyser analyser;
	std::string str_lvl;
    char str[3];
    sprintf(str, "%d", level);	 
	str_lvl = str;
	analyser.open(LEVELS_R + "level" + str_lvl + ".lvl");
	analyser.find_string("#Level_dimensions#");
	m_collisions_matrix_w = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
	m_collisions_matrix_h = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
    /*** Allocation du tableau pour les collisions ***/
    m_collisions_matrix = new uint32_t*[m_collisions_matrix_w + 1];     
    for(uint32_t i = 0; i<m_collisions_matrix_w ;i++) {
        m_collisions_matrix[i] = new uint32_t[m_collisions_matrix_h + 1];
    }
    /*** Remplissage de la matrice pour les collisions ***/
    for(uint32_t i = 0;i<m_collisions_matrix_w;i++) {
        for(uint32_t j = 0;j<m_collisions_matrix_h;j++) {
            m_collisions_matrix[i][j] = NO_COLL;
        }
    }
    analyser.find_string("#Statics#");
	std::string static_pic_rep = PIC_STATICS_R;
	std::string static_name = analyser.read_string();
	Analyser analyser_static;
	uint32_t static_weight, static_height;
    while(static_name[0]!='!') {
		int x = analyser.read_int();
		int y = analyser.read_int();
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
	

	analyser.close();
	
}

bool Collisions_manager::check_collision(Rect A, Rect B) //Optimisable?
{
	uint16_t A_right = A.x + A.w;
	uint16_t B_right = B.x + B.w;
	uint16_t A_bottom = A.y + A.h;
	uint16_t B_bottom = B.y + B.h;
	bool A_in_B = ((B.x < A.x && A.x < B_right) || (B.x < A_right && A_right < B_right )) && ((B.y < A.y && A.y < B_bottom) || (B.y < A_bottom && A_bottom < B_bottom ));
	bool B_in_A = ((A.x < B.x && B.x < A_right) || (A.x < B_right && B_right < A_right )) && ((A.y < B.y && B.y < A_bottom) || (A.y < B_bottom && B_bottom < A_bottom ));
	return A_in_B || B_in_A;
}

uint32_t Collisions_manager::collision(uint32_t x, uint32_t y)
{
    return m_collisions_matrix[x/BOX_SIZE][y/BOX_SIZE];
}

uint32_t Collisions_manager::down_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t i = pos.x ; i <= (pos.x + pos.w) ; i += BOX_SIZE)
		if (i / BOX_SIZE < m_collisions_matrix_w)
			coll |= m_collisions_matrix[i / BOX_SIZE][(pos.y + pos. h) / BOX_SIZE + 1] ;
	return coll;
}

uint32_t Collisions_manager::up_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t i = pos.x ; i < (pos.x + pos.w) ; i += BOX_SIZE)
		if (i / BOX_SIZE < m_collisions_matrix_w)
			coll |= m_collisions_matrix[i / BOX_SIZE][pos.y /  BOX_SIZE - 1] ;
	return coll;
}

uint32_t Collisions_manager::right_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t j = pos.y ; j <= (pos.y + pos.h) ; j += BOX_SIZE)
		if (j / BOX_SIZE < m_collisions_matrix_h)
			coll |= m_collisions_matrix[(pos.x + pos.w)/ BOX_SIZE + 1][j / BOX_SIZE];
	return coll;
}

uint32_t Collisions_manager::left_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t j = pos.y ; j <= (pos.y + pos.h) ; j += BOX_SIZE)
		if (j / BOX_SIZE < m_collisions_matrix_h)
			coll |= m_collisions_matrix[pos.x / BOX_SIZE - 1][j / BOX_SIZE];
		
	return coll;
}

bool Collisions_manager::up_collision(Rect pos)
{
	return is_up_coll(up_collision_type(pos));
}

bool Collisions_manager::down_collision(Rect pos)
{
	return is_down_coll(up_collision_type(pos));
}

bool Collisions_manager::left_collision(Rect pos)
{
	return is_left_coll(up_collision_type(pos));
}

bool Collisions_manager::right_collision(Rect pos)
{
	return is_right_coll(up_collision_type(pos));
}

bool Collisions_manager::double_collision(Rect pos)
{
	for (int32_t i = pos.x / BOX_SIZE ; i <= (pos.x + pos.w) / BOX_SIZE ; i += 1) {
		if (m_collisions_matrix[i][(pos.y + pos. h) / BOX_SIZE] == FULL_COLL) {
			return true;
		}
//~ 		if(m_collisions_matrix[i][(pos.y + pos. h) / BOX_SIZE ] != NO_COLL 
//~ 				&& m_collisions_matrix[i][(pos.y + pos. h) / BOX_SIZE + 1] != NO_COLL) {
//~ 			return true;
//~ 		}
	}
	return false;
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

