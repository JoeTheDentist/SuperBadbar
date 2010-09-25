
#include <iostream>
#include <stdint.h>
#include <string>

#include "static_data.h"
#include "debug.h"
#include "analyser.h"
#include "collisions.h"
#include "game.h"
#include "globals.h"
#include "sprites.h"
#include "camera.h"
#include "statics.h"


Static_data::Static_data()
{
	PRINT_CONSTR(1, "Construction d'un Static_data")

}

Static_data::Static_data(uint32_t lvl)
{
	PRINT_CONSTR(1, "Construction d'un Static_data")
	m_static_data = lvl;
    char str[3];
    std::string str_lvl;
    Analyser analyser;

	/*** chargement du fond d'écran ***/
    sprintf(str, "%d", lvl);
    str_lvl = str;
    m_background = SDL_LoadBMP(("../pic/backgrounds/level"+str_lvl+".bmp").c_str());
	
		/*** Images des projectiles ***/
    m_proj_pics[0] = SDL_LoadBMP("../pic/projectiles/left-right.bmp");
    m_proj_pics[1] = SDL_LoadBMP("../pic/projectiles/up-down.bmp");
    m_proj_pics[2] = SDL_LoadBMP("../pic/projectiles/top-left.bmp");
    m_proj_pics[3] = SDL_LoadBMP("../pic/projectiles/top-right.bmp");
	for(int i = 0;i<4;i++) {
        SDL_SetColorKey(m_proj_pics[i], SDL_SRCCOLORKEY, SDL_MapRGB(m_proj_pics[i]->format, 0, 0, 255));
    }

    /*** Remplissage des statics (et plus tard des monstres) par lecture dans un fichier ***/
    analyser.open("../data/levels/level"+str_lvl+".lvl");
    analyser.fill_statics(this);

    /*** Remplissage des monstres ***/
    m_nb_monsters = analyser.nb_monsters();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            m_monsters_pics[i][j] = new SDL_Surface*[m_nb_monsters];
        }
    }
    analyser.fill_monsters_pics(m_nb_monsters, this);


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
	analyser.fill_collision_matrix(m_collision_matrix);
    analyser.close();
}

Static_data::~Static_data()
{
	PRINT_CONSTR(1, "Destruction d'un Static_data")
    for(uint32_t i = 0; i<(static_data_weight()/BOX_SIZE + 1);i++) {
        delete[] m_collision_matrix[i];
    }
    delete[] m_collision_matrix;

    for(int i=0;i<2;i++) {
        for(int j=0;j<4;j++) {
            for(int l=0;l<m_nb_monsters;l++) {
                SDL_FreeSurface(m_monsters_pics[i][j][l]);
            }
            delete[] m_monsters_pics[i][j];
        }
    }
	
	for(int i = 0;i<4;i++) {
        SDL_FreeSurface(m_proj_pics[i]);
    }


    SDL_FreeSurface(m_background);

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
    return m_background->h / BACKGROUND_SPEED - WINDOW_HEIGHT;
}

uint32_t Static_data::static_data_weight()
{
    return m_background->w / BACKGROUND_SPEED - WINDOW_WEIGHT;
}

uint32_t Static_data::collision(uint32_t x, uint32_t y)
{
    return m_collision_matrix[x/BOX_SIZE][y/BOX_SIZE];
}


uint32_t Static_data::down_collision_type(SDL_Rect pos)
{
	uint32_t coll = 0;
	for (int32_t i = pos.x ; i <= (pos.x + pos.w) ; i += BOX_SIZE)
		coll |= m_collision_matrix[i / BOX_SIZE][(pos.y + pos. h) / BOX_SIZE + 1] ;
	return coll;
}

uint32_t Static_data::up_collision_type(SDL_Rect pos)
{
	uint32_t coll = 0;
	for (int32_t i = pos.x ; i < (pos.x + pos.w) ; i += BOX_SIZE)
		coll |= m_collision_matrix[i / BOX_SIZE][pos.y /  BOX_SIZE - 1] ;
	return coll;
}

uint32_t Static_data::right_collision_type(SDL_Rect pos)
{
	uint32_t coll = 0;
	for (int32_t j = pos.y ; j <= (pos.y + pos.h) ; j += BOX_SIZE)
		coll |= m_collision_matrix[(pos.x + pos.w)/ BOX_SIZE + 1][j / BOX_SIZE];
	return coll;
}

uint32_t Static_data::left_collision_type(SDL_Rect pos)
{
	uint32_t coll = 0;
	for (int32_t j = pos.y ; j <= (pos.y + pos.h) ; j += BOX_SIZE)
		coll |= m_collision_matrix[pos.x / BOX_SIZE - 1][j / BOX_SIZE];
	return coll;
}

bool Static_data::up_collision(SDL_Rect pos)
{
	return is_up_coll(up_collision_type(pos));
}


bool Static_data::down_collision(SDL_Rect pos)
{
	return is_down_coll(up_collision_type(pos));
}


bool Static_data::left_collision(SDL_Rect pos)
{
	return is_left_coll(up_collision_type(pos));
}


bool Static_data::right_collision(SDL_Rect pos)
{
	return is_right_coll(up_collision_type(pos));
}


bool Static_data::double_collision(SDL_Rect pos)
{
	for (int32_t i = pos.x / BOX_SIZE ; i <= (pos.x + pos.w) / BOX_SIZE ; i += 1) {
		if (!(m_collision_matrix[i][pos.y + pos. h - 1] == NO_COLL || m_collision_matrix[i][pos.y + pos. h- 1] == DOWN_COLL))
			return true;
		if(m_collision_matrix[i][pos.y + pos. h - 1] != NO_COLL && m_collision_matrix[i][pos.y + pos. h] != NO_COLL)
			return true;
	}
	return false;
}

void Static_data::fill_monster_pic(int h, int num_image, int num_monster, char *link)
{
    m_monsters_pics[h][num_image][num_monster] = SDL_LoadBMP(link);
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


bool to_delete(Monster * monster, Dynamic_data *dynamic_data, Camera *camera)
{
    SDL_Rect monster_pos = monster->position();
    SDL_Rect camera_pos = camera->frame();

    if(!check_collision(monster_pos,camera_pos)) {  /* Il est trop cool ce Gloups */
        /* Ici le monstres n'est pas dans l'écran de caméra */
        dynamic_data->fill_monster(monster_pos.y/BOX_SIZE,monster_pos.x/BOX_SIZE,monster);    /*On remet le monstre dans le tableau */
        return true;
    }
    return false;
}
