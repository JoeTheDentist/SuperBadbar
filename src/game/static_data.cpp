
#include <iostream>
#include <stdint.h>
#include <string>

#include "static_data.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../game/game.h"
#include "../util/globals.h"
#include "../sprites/sprites.h"
#include "../sprites/monsters.h"
#include "../video/camera.h"
#include "../video/statics.h"
#include "../video/pictures_container.h"
#include "../video/surface.h"


Static_data::Static_data() : m_pictures_container(new Pictures_container())
{
	PRINT_CONSTR(1, "Construction d'un Static_data")

}

Static_data::~Static_data()
{
	PRINT_CONSTR(1, "Destruction d'un Static_data")
	delete m_pictures_container;
	for(std::list<Static *>::iterator it = m_statics.begin();
			it != m_statics.end(); it++) {
	    delete (*it);
	}
	delete m_background;

}

void Static_data::init_static_data(uint32_t lvl)
{
	std::string rep;
    std::string rac = RAC;
	PRINT_CONSTR(1, "Construction d'un Static_data")
    char str[3];
    std::string str_lvl;
    Analyser analyser;

	/*** chargement du fond d'écran ***/
    sprintf(str, "%d", lvl);
    str_lvl = str;
    m_background = new Surface(PIC_BACKGROUNDS_R + "level"+str_lvl+".png");

	/*** Images des projectiles ***/
	rep = PIC_PROJ_R;
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


    analyser.close();
}


Surface * Static_data::background()
{
    return m_background;
}

uint32_t Static_data::static_data_height()
{
    return m_background->h() / BACKGROUND_SPEED - WINDOW_HEIGHT ;
}

uint32_t Static_data::static_data_weight()
{
    return m_background->w() / BACKGROUND_SPEED - WINDOW_WEIGHT;
}





Pictures_container *Static_data::get_pictures_container()
{
	return m_pictures_container;
}

void Static_data::display_statics(Camera *camera)
{
	for(std::list<Static *>::iterator it = m_statics.begin();
			it != m_statics.end(); it++) {
	    camera->display((*it));
	}
}

void Static_data::add_static(Static *stat)
{
	m_statics.push_back(stat);
}

