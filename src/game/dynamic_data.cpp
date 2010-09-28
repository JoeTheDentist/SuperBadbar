#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <string>

#include "dynamic_data.h"
#include "../game/static_data.h"
#include "../sound/sound_manager.h"
#include "../control/keyboard.h"
#include "../util/debug.h"
#include "../sprites/sprites.h"
#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sprites/walking_monsters.h"
#include "../sprites/projectiles.h"
#include "../util/analyser.h"
#include "../video/camera.h"
#include "../util/collisions.h"
#include "../util/globals.h"
#include "../control/keyboard.h"



Dynamic_data::Dynamic_data()
{

}


Dynamic_data::Dynamic_data(Camera *camera, Static_data *static_data, Sound_manager *sound_manager, Keyboard *keyboard)
{
    std::string rac = RAC;
	PRINT_CONSTR(1, "Construction de la classe Dynamic_data")
	m_sound_manager = sound_manager;
	m_matrix_weight = static_data->static_data_weight();
	m_matrix_height = static_data->static_data_height();
	std::string str_lvl = "1";
	Analyser analyser, analyser2;
	analyser.open(rac+"/data/levels/level"+str_lvl+".lvl");
    /* Allocation de la matrice de monstres */
    m_monsters_matrix = new Monster**[m_matrix_weight + 1];
    for(uint32_t i = 0; i<(m_matrix_weight);i++) {
        m_monsters_matrix[i] = new Monster*[m_matrix_height + 1];
    }
    for(uint32_t i = 0;i<(m_matrix_weight);i++) {
        for(uint32_t j = 0;j<(m_matrix_height);j++) {
            m_monsters_matrix[i][j] = NULL;
		}
    }
    analyser2.open(rac+"/data/levels/level"+str_lvl+".lvl");
    analyser.fill_monsters(&analyser2, static_data, this);
    analyser2.close();
	m_babar = new Babar(&m_projectiles_friend, keyboard, static_data, sound_manager);

    /*** Stockage des monstres dans la listes ***/
	SDL_Rect camera_frame, position_target = m_babar->position();
	camera_frame.h = WINDOW_HEIGHT;
	camera_frame.w = WINDOW_WEIGHT;
	camera_frame.x = position_target.x + (position_target.w / 2) - (camera_frame.w / 2);
	camera_frame.y = position_target.y + (position_target.h / 2) - (camera_frame.h / 2);
	if (camera_frame.x < 0)
		camera_frame.x = 0;
	if (camera_frame.y < 0)
		camera_frame.y = 0;
	if ((uint32_t) (camera_frame.x + camera_frame.w) > static_data->static_data_weight())
		camera_frame.x = static_data->static_data_weight() - camera_frame.w;
	if ((uint32_t) (camera_frame.y + camera_frame.h) > static_data->static_data_height())
		camera_frame.y = static_data->static_data_height() - camera_frame.h;

	for(uint32_t i= camera_frame.x/BOX_SIZE;i<(uint32_t)(camera_frame.w+camera_frame.x)/BOX_SIZE;i++) {
        for(uint32_t j=camera_frame.y/BOX_SIZE;j<(uint32_t)(camera_frame.h+camera_frame.y)/BOX_SIZE;j++) {
            if(m_monsters_matrix[i][j] != NULL) {
                m_monsters.add(m_monsters_matrix[i][j]);
                m_monsters_matrix[i][j] = NULL;
            }
        }
    }/**/


	analyser.close();
}

Dynamic_data::~Dynamic_data()
{
	for(uint32_t i = 0;i<(m_matrix_weight);i++) {
        for(uint32_t j = 0;j<(m_matrix_height);j++) {
            if (m_monsters_matrix[i][j] != NULL) {
                delete m_monsters_matrix[i][j];
            }
        }
    }
	for(uint32_t i = 0; i<(m_matrix_weight);i++)
		delete[] m_monsters_matrix[i];
    delete[] m_monsters_matrix;

}

bool Dynamic_data::projectiles_friend_end()
{
	return 	m_projectiles_friend.end();
}


void Dynamic_data::projectiles_friend_update_pos(Static_data *static_data)
{
	while(!m_projectiles_friend.end()) {
	    m_projectiles_friend.element()->update_pos(static_data);
	    m_projectiles_friend.next();
	}
	m_projectiles_friend.init();
}

void Dynamic_data::babar_update_pos(Static_data *static_data)
{
	m_babar->update_pos(static_data);
}


void Dynamic_data::monsters_update_pos(Static_data*static_data)
{
	while(!m_monsters.end()) {
		m_monsters.element()->update_pos(static_data);
		m_monsters.next();
	}
		m_monsters.init();
}

void Dynamic_data::babar_update_speed()
{
	m_babar->update_speed();
}

void Dynamic_data::babar_update_state(Static_data *static_data)
{
	m_babar->update_state(static_data);
}

void Dynamic_data::babar_monsters_collision()
{
	SDL_Rect babar_pos = m_babar->position();
	while(!m_monsters.end()) {
		if (check_collision(m_monsters.element()->position(), babar_pos)) {
			m_babar->damage(1);
		}
	    m_monsters.next();
	}
	m_monsters.init();
}

void Dynamic_data::monsters_update_speed()
{
	while(!m_monsters.end()) {
	    m_monsters.element()->update_speed();
	    m_monsters.next();
	}
	m_monsters.init();
}

void Dynamic_data::display_monsters(Camera *camera)
{
	while(!m_monsters.end()) {
	    camera->display_sprite(m_monsters.element());
	    m_monsters.next();
	}
	m_monsters.init();
}


void Dynamic_data::display_projectiles_friend(Camera *camera)
{
	while(!projectiles_friend_end()) {
	    camera->display_sprite(m_projectiles_friend.element());
	    m_projectiles_friend.next();
	}
}

void Dynamic_data::delete_old_projectiles_friend(Static_data *static_data)
{
    m_projectiles_friend.delete_elements(too_old, static_data);
}

void Dynamic_data::update_monsters_projectiles()
{
   m_monsters.delete_elements(to_kill, &m_projectiles_friend);
}




void Dynamic_data::fill_monster(uint32_t i, uint32_t j, Monster * monster)
{
    m_monsters_matrix[i][j] = monster;
}


void Dynamic_data::fill_monster_stats(uint32_t i, uint32_t j, uint32_t monster_type, uint32_t begin, uint32_t end, uint32_t life, bool fire, uint32_t speed, Static_data *static_data)
{
    Monster * curr_monster = new Walking_monster(m_sound_manager);
    curr_monster->set_type(monster_type);
    curr_monster->set_pos_x(j*BOX_SIZE);
    curr_monster->set_pos_y(i*BOX_SIZE);
    curr_monster->set_begin(begin);
    curr_monster->set_end(end);
    curr_monster->set_life(life);
    curr_monster->set_fire(fire);
    curr_monster->set_speed(speed);
    for(int k=0;k<2;k++) {
        for(int l=0;l<4;l++) {
			SDL_Surface **monster_pics = static_data->monster_pic(k, l);
            curr_monster->set_pic(monster_pics[monster_type],k,l);
//~ 			curr_monster->set_pic(monster_pics[k][l][monster_type],k,l);

        }
    }
    m_monsters_matrix[i][j] = curr_monster;
}



void Dynamic_data::update(Camera *camera)
/* Optimisable ! Pas besoin de tout recharger */
{
    SDL_Rect last_pos = camera->frame();
    m_monsters.delete_elements(to_delete, this, camera);
    for(int i=last_pos.y/BOX_SIZE;i<(last_pos.h+last_pos.y)/BOX_SIZE;i++) {
        for(int j=last_pos.x/BOX_SIZE;j<(last_pos.w+last_pos.x)/BOX_SIZE;j++) {
            if(m_monsters_matrix[i][j] != NULL) {
                /*Monster * mstr = new Monster;
                mstr = m_monsters_matrix[i][j];*/
                m_monsters.add(m_monsters_matrix[i][j]);
                m_monsters_matrix[i][j] = NULL;
            }
        }
    }
}

List<Projectile*> *Dynamic_data::projectiles_friend()
{
	return &m_projectiles_friend;
}


Babar *Dynamic_data::babar()
{
	return m_babar;
}


/*** Fonctions ***/

bool to_kill(Monster * monster, List<Projectile*> *projectiles_friend)
{
    /* On supprime les projectiles qui en on besoin */
    projectiles_friend->delete_elements(check_monster_proj, monster);

    /* On retourne si le monstre est mort */
    if(monster->dead()) {
        delete monster;
        return true;
    }
    return false;
}

bool check_monster_proj(Projectile * proj, Monster * monster)
{
    /* Regarde si un monstre est en collision avec un projectile, si c'est le cas on fait perdre des vies au monstre et on retourne vrai => pour suppr le projectile */
    if(check_collision(monster->position(),proj->position())) {
        monster->damage(proj->damage());
        return true;
    }
    return false;
}
