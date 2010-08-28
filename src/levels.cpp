
#include <iostream>
#include <stdint.h>
#include <string>

#include "levels.h"
#include "analyser.h"
#include "collisions.h"
#include "game.h"
#include "sprites.h"


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
    /*analyser.close();*/

    /*** Remplissage des monstres ***/
    /*analyser.open("../data/levels/level"+str_lvl+".lvl");*/
    m_nb_monsters = analyser.nb_monsters();
	fprintf(stderr, "%d", m_nb_monsters);
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            for(int k=0;k<3;k++) {
                m_monsters_pics[i][j][k] = new SDL_Surface*[m_nb_monsters];
            }
        }
    }
    analyser.fill_monsters_pics(m_nb_monsters);
    /* Allocation de la matrice de monstres */
    m_monsters_matrix = new Monster*[m_background->h/BOX_SIZE];
    for(int i = 0; i<(m_background->h/BOX_SIZE);i++) {
        m_monsters_matrix[i] = new Monster[m_background->w/BOX_SIZE];
    }
    for(int i = 0;i<(m_background->h/BOX_SIZE);i++) {
        for(int j = 0;j<(m_background->w/BOX_SIZE);j++) {
            m_monsters_matrix[i][j].set_type(-1);
        }
    }
    Analyser analyser2;
    analyser2.open("../data/levels/level"+str_lvl+".lvl");
    analyser.fill_monsters(&analyser2);
    analyser2.close();
    analyser.close();


    /*** Stockage des monstres dans la listes ***/
    game.update_camera();
    m_last_pos = game.camera_frame();
    SDL_Rect blabla = m_last_pos;
    for(int i=m_last_pos.y/BOX_SIZE;i<(m_last_pos.h+m_last_pos.y)/BOX_SIZE;i++) {
        for(int j=m_last_pos.x/BOX_SIZE;j<(m_last_pos.w+m_last_pos.x)/BOX_SIZE;j++) {
            if(m_monsters_matrix[i][j].type() != -1) {
                Monster * mstr = new Monster;
                *mstr = m_monsters_matrix[i][j];
                monsters.add(mstr);
                m_monsters_matrix[i][j].set_type(-1);
            }
        }
    }


    /*** Allocation du tableau pour les collisions ***/
    m_collision_matrix = new uint32_t*[m_background->h/BOX_SIZE];     /* Il est préférable que le fond soit de dimension divisible par BOX_SIZE*/
    for(int i = 0; i<(m_background->h/BOX_SIZE);i++) {
        m_collision_matrix[i] = new uint32_t[m_background->w/BOX_SIZE];
    }

    /*** Remplissage de la matrice pour les collisions ***/
    for(int i = 0;i<(m_background->h/BOX_SIZE);i++) {
        for(int j = 0;j<(m_background->w/BOX_SIZE);j++) {
            m_collision_matrix[i][j] = NO_COLL;
        }
    }
    for(int i = 0;i<(m_background->w/BOX_SIZE);i++) {           /* Temp, on met le sol intraversable */
		m_collision_matrix[i][(m_background->h/BOX_SIZE)-1] = FULL_COLL;
		if (i < 20 || i > 90){
			m_collision_matrix[i][(m_background->h/BOX_SIZE)-30] = DOWN_COLL;
			m_collision_matrix[i][(m_background->h/BOX_SIZE)-60] = DOWN_COLL;
			m_collision_matrix[i][(m_background->h/BOX_SIZE)-90] = DOWN_COLL;
			m_collision_matrix[i][(m_background->h/BOX_SIZE)-150] = FULL_COLL;
		}
    }
	//~ for (int i = 0 ; i < 100 ; i++){
		//~ m_collision_matrix[i][i] = FULL_COLL;
	//~ }
}

Level::~Level()
{
    for(int i = 0; i<(m_background->h/BOX_SIZE);i++) {
        delete m_collision_matrix[i];
    }
    delete m_collision_matrix;

    SDL_FreeSurface(m_background);

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            for(int k=0;k<3;k++) {
                for(int l=0;l<m_nb_monsters;l++) {
                    SDL_FreeSurface(m_monsters_pics[i][j][k][l]);
                }
                delete[] m_monsters_pics[i][j][k];
            }
        }
    }
}

void Level::fill_collision(uint32_t i, uint32_t j, uint32_t collision_type)
{
    //~ uint32_t a = m_collision_matrix[0][0];
    m_collision_matrix[i][j] = collision_type;
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
    return m_collision_matrix[i/BOX_SIZE][j/BOX_SIZE];
}


bool Level::down_collision(SDL_Rect pos)
{
	for (int32_t i = pos.x ; i < (pos.x + pos.w) ; i += BOX_SIZE) {
		if (down_coll(m_collision_matrix[i / BOX_SIZE][(pos.y + pos. h) / BOX_SIZE]))
			return true;
	}
	return false;
}

bool Level::up_collision(SDL_Rect pos)
{
	for (int32_t i = pos.x ; i < (pos.x + pos.w) ; i += BOX_SIZE) {
		if (up_coll(m_collision_matrix[i / BOX_SIZE][pos.y / BOX_SIZE]))
			return true;
	}
	return false;
}

void Level::fill_monster_pic(int state, int h, int num_image, int num_monster, char *link)
{
    m_monsters_pics[state][h][num_image][num_monster] = SDL_LoadBMP(link);
    SDL_SetColorKey(m_monsters_pics[state][h][num_image][num_monster], SDL_SRCCOLORKEY, SDL_MapRGB(m_monsters_pics[state][h][num_image][num_monster]->format, 0, 0, 255));

}

void Level::fill_monster_pos(uint32_t i, uint32_t j, uint32_t monster_type, uint32_t begin, uint32_t end, uint32_t life, bool fire, uint32_t speed)
{
    m_monsters_matrix[i][j].set_type(monster_type);
    m_monsters_matrix[i][j].set_pos_x(j*BOX_SIZE);
    m_monsters_matrix[i][j].set_pos_y(i*BOX_SIZE);
    m_monsters_matrix[i][j].set_begin(begin);
    m_monsters_matrix[i][j].set_end(end);
    m_monsters_matrix[i][j].set_life(life);
    m_monsters_matrix[i][j].set_fire(fire);
    m_monsters_matrix[i][j].set_speed(speed);
    for(int k=0;k<3;k++) {
        for(int l=0;l<3;l++) {
            for(int m=0;m<3;m++) {
                m_monsters_matrix[i][j].set_pic(m_monsters_pics[k][l][m][monster_type],k,l,m);
            }
        }
    }
}

void Level::fill_monster(uint32_t i, uint32_t j, Monster monster)
{
    m_monsters_matrix[i][j] = monster;
}

void Level::update()
{
    m_last_pos = game.camera_frame();
    monsters.delete_elements(to_delete);
    for(int i=m_last_pos.y/BOX_SIZE;i<(m_last_pos.h+m_last_pos.y)/BOX_SIZE;i++) {
        for(int j=m_last_pos.x/BOX_SIZE;j<(m_last_pos.w+m_last_pos.x)/BOX_SIZE;j++) {
            if(m_monsters_matrix[i][j].type() != -1) {
                Monster * mstr = new Monster;
                *mstr = m_monsters_matrix[i][j];
                monsters.add(mstr);
                m_monsters_matrix[i][j].set_type(-1);
            }
        }
    }
}


bool to_delete(Monster * monster)
{
    SDL_Rect monster_pos = monster->position();
    SDL_Rect camera_pos = game.camera_frame();

    if(!check_collision(monster_pos,camera_pos)) {  /* Il est trop cool ce Gloups */
        /* Ici le monstres n'est pas dans l'écran de caméra */
        curr_lvl.fill_monster(monster_pos.y/BOX_SIZE,monster_pos.x/BOX_SIZE,*monster);    /*On remet le monstre dans le tableau */
        return true;
    }
    return false;
}
