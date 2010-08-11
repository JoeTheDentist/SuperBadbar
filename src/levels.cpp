
#include <iostream>
#include <stdint.h>
#include <string>

#include "levels.h"
#include "analyser.h"
#include "collisions.h"


Level::Level()
{
}

Level::Level(uint32_t lvl)
{
	m_level = lvl;
    char str[3];
    std::string str_lvl;
    Analyser analyser;
    sprintf(str, "%d", lvl);    /* convertion int vers tableau de char, je n'ai pas trouvé avec les strings */
    str_lvl = str;

    m_background = SDL_LoadBMP(("../pic/backgrounds/level"+str_lvl+".bmp").c_str());    /*...besoin d'un tableau de char...*/

    /*** Remplissage des statics (et plus tard des monstres) par lecture dans un fichier ***/
    analyser.open("../data/levels/level"+str_lvl+".lvl");
    analyser.fill_statics();
    analyser.close();

    /*** Allocation du tableau pour les collisions ***/
    m_statics_matrix = new uint32_t*[m_background->h/BOX_SIZE];     /* Il est préférable que le fond soit de dimension divisible par BOX_SIZE*/
    for(int i = 0; i<(m_background->h/BOX_SIZE);i++) {
        m_statics_matrix[i] = new uint32_t[m_background->w/BOX_SIZE];
    }

    /*** Remplissage de la matrice pour les collisions ***/
    for(int i = 0;i<(m_background->h/BOX_SIZE);i++) {
        for(int j = 0;j<(m_background->w/BOX_SIZE);j++) {
            m_statics_matrix[i][j] = NO_COLL;
        }
    }
    for(int i = 0;i<(m_background->w/BOX_SIZE);i++) {           /* Temp, on met le sol intraversable */
		m_statics_matrix[i][(m_background->h/BOX_SIZE)-1] = FULL_COLL;
		if (i < 20 || i > 90){
			m_statics_matrix[i][(m_background->h/BOX_SIZE)-30] = DOWN_COLL;
			m_statics_matrix[i][(m_background->h/BOX_SIZE)-60] = DOWN_COLL;
			m_statics_matrix[i][(m_background->h/BOX_SIZE)-90] = DOWN_COLL;
			m_statics_matrix[i][(m_background->h/BOX_SIZE)-150] = FULL_COLL;
		}
    }
	//~ for (int i = 0 ; i < 100 ; i++){
		//~ m_statics_matrix[i][i] = FULL_COLL;
	//~ }

    m_proj[0] = SDL_LoadBMP("../pic/projectiles/left-right.bmp");
    m_proj[1] = SDL_LoadBMP("../pic/projectiles/up-down.bmp");
    m_proj[2] = SDL_LoadBMP("../pic/projectiles/top-left.bmp");
    m_proj[3] = SDL_LoadBMP("../pic/projectiles/top-right.bmp");
}

Level::~Level()
{
    for(int i = 0; i<(m_background->h/BOX_SIZE);i++) {
        delete m_statics_matrix[i];
    }
    delete m_statics_matrix;
    SDL_FreeSurface(m_background);
    for(int i = 0;i<4;i++) {
        SDL_FreeSurface(m_proj[i]);
    }
}

void Level::fill_collision(uint32_t i, uint32_t j, uint32_t collision_type)
{
    //~ uint32_t a = m_statics_matrix[0][0];
    m_statics_matrix[i][j] = collision_type;
}

SDL_Surface * Level::background()
{
    return m_background;
}

uint32_t Level::level_height()
{
    return m_background->h;
}

uint32_t Level::level_weight()
{
    return m_background->w;
}

uint32_t Level::collision(uint32_t i, uint32_t j)
{
    return m_statics_matrix[i/BOX_SIZE][j/BOX_SIZE];
}

SDL_Surface * Level::proj(uint8_t i)
{
    return m_proj[i];
}



bool Level::down_collision(SDL_Rect pos)
{
	for (int32_t i = pos.x ; i < (pos.x + pos.w) ; i += BOX_SIZE) {
		if (down_coll(m_statics_matrix[i / BOX_SIZE][(pos.y + pos. h) / BOX_SIZE]))
			return true;
	}
	return false;
}

bool Level::up_collision(SDL_Rect pos)
{
	for (int32_t i = pos.x ; i < (pos.x + pos.w) ; i += BOX_SIZE) {
		if (up_coll(m_statics_matrix[i / BOX_SIZE][pos.y / BOX_SIZE]))
			return true;
	}
	return false;
}


