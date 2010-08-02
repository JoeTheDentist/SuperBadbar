
#include <iostream>
#include <stdint.h>
#include <string>

#include "levels.h"
#include "analyser.h"


Level::Level()
{
}

Level::Level(uint32_t lvl)
{
	m_level = lvl;
    char str[3];
    std::string str_lvl;
    Analyser analyser;
    itoa(lvl,str,10);     /* convertion int vers tableau de char, je n'ai pas trouvé avec les strings */
    str_lvl = str;

    m_background = SDL_LoadBMP(("../pic/backgrounds/level"+str_lvl+".bmp").c_str());    /*...besoin d'un tableau de char...*/

    /*** Remplissage des statics (et plus tard des monstres) par lecture dans un fichier ***/
    analyser.open("../data/levels/level"+str_lvl+".lvl");
    analyser.fill_statics();
    analyser.close();

    /*** Allocation du tableau pour les collisions ***/
    m_statics_matrix = new uint8_t*[m_background->h/BOX_SIZE];     /* Il est préférable que le fond soit de dimension divisible par BOX_SIZE*/
    for(int i = 0; i<(m_background->h/BOX_SIZE);i++) {
        m_statics_matrix[i] = new uint8_t[m_background->w/BOX_SIZE];
    }

    /*** Remplissage de la matrice pour les collisions ***/
    for(int i = 0;i<(m_background->h/BOX_SIZE);i++) {
        for(int j = 0;j<(m_background->w/BOX_SIZE);j++) {
            m_statics_matrix[i][j] = 0;
        }
    }
    for(int i = 0;i<(m_background->w/BOX_SIZE);i++) {           /* Temp, on met le sol intraversable */
        m_statics_matrix[(m_background->h/BOX_SIZE)-1][i] = 1;
    }


}

Level::~Level()
{
    for(int i = 0; i<(m_background->h/BOX_SIZE);i++) {
        delete m_statics_matrix[i];
    }
    delete m_statics_matrix;
    SDL_FreeSurface(m_background);
}

void Level::fill_collision(uint32_t i, uint32_t j, uint8_t collision_type)
{
    uint32_t a = m_statics_matrix[0][0];
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

uint8_t Level::collision(uint32_t i, uint32_t j)
{
    return m_statics_matrix[i][j];
}
