
#include <iostream>
#include <stdint.h>
#include <string>

#include "static_data.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../util/collisions.h"
#include "../game/game.h"
#include "../util/globals.h"
#include "../sprites/sprites.h"
#include "../sprites/monsters.h"
#include "../video/camera.h"
#include "../video/statics.h"
#include "../video/pictures_container.h"


Static_data::Static_data() : m_pictures_container(new Pictures_container())
{
	PRINT_CONSTR(1, "Construction d'un Static_data")

}

Static_data::~Static_data()
{
	PRINT_CONSTR(1, "Destruction d'un Static_data")
    for(uint32_t i = 0; i<(static_data_weight()/BOX_SIZE + 1);i++) {
        delete[] m_collision_matrix[i];
    }
    delete[] m_collision_matrix;
    m_statics.~List();
	delete m_pictures_container;

}

void Static_data::init_static_data(uint32_t lvl)
{
    m_statics.void_list();
	std::string rep;
    std::string rac = RAC;
	PRINT_CONSTR(1, "Construction d'un Static_data")
	m_static_data = lvl;
    char str[3];
    std::string str_lvl;
    Analyser analyser;

	/*** chargement du fond d'écran ***/
    sprintf(str, "%d", lvl);
    str_lvl = str;
    m_background = m_pictures_container->load_BMP((PIC_BACKGROUNDS_R + "level"+str_lvl+".bmp").c_str());

	/*** Images des projectiles ***/
	rep = PIC_PROJ_R;
    m_proj_pics[0] = m_pictures_container->load_BMP((rep + "left-right.bmp").c_str());
    m_proj_pics[1] = m_pictures_container->load_BMP((rep + "up-down.bmp").c_str());
    m_proj_pics[2] = m_pictures_container->load_BMP((rep + "top-left.bmp").c_str());
    m_proj_pics[3] = m_pictures_container->load_BMP((rep + "top-right.bmp").c_str());

    /*** Remplissage des statics  ***/
	rep = LEVELS_R;
    analyser.open(rep + "level" + str_lvl + ".lvl");
	
	
	std::string static_pic_rep = PIC_STATICS_R;
	std::string static_name;
    analyser.find_string("#Statics#");
	static_name = analyser.read_string();
	Rect pos;
	Static *curr_static;
	while(static_name[0]!='!') {
		pos.x = analyser.read_int();
		pos.y = analyser.read_int();
        curr_static = new Static(static_pic_rep + static_name + PICS_EXT,pos);
		static_name = analyser.read_string();
		add_static(curr_static);
    }

    /*** Allocation du tableau pour les collisions ***/
    m_collision_matrix = new uint32_t*[static_data_weight()/BOX_SIZE + 1];     /* Il est préférable que le fond soit de dimension divisible par BOX_SIZE*/
    for(uint32_t i = 0; i<(static_data_weight()/BOX_SIZE+1);i++) {
        m_collision_matrix[i] = new uint32_t[static_data_height()/BOX_SIZE + 1];
    }

    /*** Remplissage de la matrice pour les collisions ***/
    for(uint32_t i = 0;i<(static_data_weight()/BOX_SIZE);i++) {
        for(uint32_t j = 0;j<(static_data_height()/BOX_SIZE);j++) {
            m_collision_matrix[i][j] = NO_COLL;
        }
    }
	
	
	analyser.find_string("#Statics#");
	static_name = analyser.read_string();
	Analyser *analyser_static = new Analyser();
	uint32_t static_weight, static_height;
    while(static_name[0]!='!') {
		int x = analyser.read_int();
		int y = analyser.read_int();
		analyser_static->open((static_pic_rep + static_name + COLL_EXT));
		static_weight = analyser_static->read_int();
		static_height = analyser_static->read_int();
		for (uint32_t j = y / BOX_SIZE ; j < y / BOX_SIZE + static_height; j++) {
			for (uint32_t i = x / BOX_SIZE; i < x / BOX_SIZE + static_weight; i++) {
				m_collision_matrix[i][j] |= analyser_static->read_uint32_t();
			}
		}
		analyser_static->close();
		static_name = analyser.read_string();
	}
	delete analyser_static;
    analyser.close();
}

void Static_data::fill_collision(uint32_t i, uint32_t j, uint32_t collision_type)
{
    m_collision_matrix[i][j] = collision_type;
}

SDL_Surface * Static_data::background()
{
    return m_background;
}

uint32_t Static_data::static_data_height()
{
    return m_background->h / BACKGROUND_SPEED;
}

uint32_t Static_data::static_data_weight()
{
    return m_background->w / BACKGROUND_SPEED;
}

uint32_t Static_data::collision(uint32_t x, uint32_t y)
{
    return m_collision_matrix[x/BOX_SIZE][y/BOX_SIZE];
}


uint32_t Static_data::down_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t i = pos.x ; i <= (pos.x + pos.w) ; i += BOX_SIZE)
		coll |= m_collision_matrix[i / BOX_SIZE][(pos.y + pos. h) / BOX_SIZE + 1] ;
	return coll;
}

uint32_t Static_data::up_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t i = pos.x ; i < (pos.x + pos.w) ; i += BOX_SIZE)
		coll |= m_collision_matrix[i / BOX_SIZE][pos.y /  BOX_SIZE - 1] ;
	return coll;
}

uint32_t Static_data::right_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t j = pos.y ; j <= (pos.y + pos.h) ; j += BOX_SIZE)
		coll |= m_collision_matrix[(pos.x + pos.w)/ BOX_SIZE + 1][j / BOX_SIZE];
	return coll;
}

uint32_t Static_data::left_collision_type(Rect pos)
{
	uint32_t coll = 0;
	for (int32_t j = pos.y ; j <= (pos.y + pos.h) ; j += BOX_SIZE)
		coll |= m_collision_matrix[pos.x / BOX_SIZE - 1][j / BOX_SIZE];
	return coll;
}

bool Static_data::up_collision(Rect pos)
{
	return is_up_coll(up_collision_type(pos));
}


bool Static_data::down_collision(Rect pos)
{
	return is_down_coll(up_collision_type(pos));
}


bool Static_data::left_collision(Rect pos)
{
	return is_left_coll(up_collision_type(pos));
}


bool Static_data::right_collision(Rect pos)
{
	return is_right_coll(up_collision_type(pos));
}


bool Static_data::double_collision(Rect pos)
{
	for (int32_t i = pos.x / BOX_SIZE ; i <= (pos.x + pos.w) / BOX_SIZE ; i += 1) {
		if (!(m_collision_matrix[i][pos.y + pos. h - 1] == NO_COLL || m_collision_matrix[i][pos.y + pos. h- 1] == DOWN_COLL))
			return true;
		if(m_collision_matrix[i][pos.y + pos. h - 1] != NO_COLL && m_collision_matrix[i][pos.y + pos. h] != NO_COLL)
			return true;
	}
	return false;
}

void Static_data::fill_monster_pic(int h, int num_image, int num_monster, const char *link)
{
    m_monsters_pics[h][num_image][num_monster] = m_pictures_container->load_BMP(link);
    SDL_SetColorKey(m_monsters_pics[h][num_image][num_monster], SDL_SRCCOLORKEY, SDL_MapRGB(m_monsters_pics[h][num_image][num_monster]->format, 0, 0, 255));

}

SDL_Surface **Static_data::monster_pic(uint32_t i, uint32_t j)
{
	return m_monsters_pics[i][j];
}

SDL_Surface **Static_data::proj_pics()
{
	return m_proj_pics;
}

Pictures_container *Static_data::get_pictures_container()
{
	return m_pictures_container;
}

void Static_data::display_statics(Camera *camera)
{
	while(!m_statics.end()) {
	    camera->display_static(m_statics.element());
	    m_statics.next();
	}
	m_statics.init();
}

void Static_data::add_static(Static *stat)
{
	m_statics.add(stat);
}
