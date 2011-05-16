/**
 * 	@file dashboard.cpp
 * 	@brief Implémentation de la classe Dashboard
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>
#include <sstream>


#include "dashboard.h"
#include "../video/camera.h"
#include "../util/debug.h"
#include "../actors/babar.h"
#include "../video/talks.h"
#include "../video/surface.h"
#include "../video/surface_text.h"
#include "../video/pictures_container.h"
#include "../util/globals.h"
#include "../players/players_manager.h"

Dashboard::Dashboard():
	m_heart(NULL),
	m_weapons_pictures(NULL),
	m_peanut(NULL),
	m_font()
{
	PRINT_CONSTR(1, "Construction de Dashboard (tableau de bord)")
	m_alert = NULL;
}


Dashboard::~Dashboard()
{
	clear_dashboard();
	PRINT_CONSTR(1, "Destruction de Dashboard")
}

void Dashboard::init_dashboard(Pictures_container *pictures_container)
{
	clear_dashboard();
    std::string rac = RAC;
	m_heart = new Surface(rac+"/pic/dashboard/heart.png");
	m_HP_pos.x = POS_HEART_X;
	m_HP_pos.y = POS_HEART_Y;
	m_weapons_pictures = new Surface*[LASTWEAPON];
	for (int i = 0; i < LASTWEAPON; i++)
		m_weapons_pictures[i] = NULL;
	m_weapons_pictures[MACHINEGUN] = new Surface(PIC_DASHBOARD_R + "weapon/machinegun.png");
	m_weapons_pictures[GUN] = new Surface(PIC_DASHBOARD_R + "weapon/gun.png");
	m_weapons_pictures[SHOTGUN] = new Surface(PIC_DASHBOARD_R + "weapon/shotgun.png");
	m_weapons_pictures[ROCKET_LAUNCHER] = new Surface(PIC_DASHBOARD_R + "weapon/rocket_launcher.png");
	m_weapons_pos.x = POS_WEAPON_X;
	m_weapons_pos.y = POS_WEAPON_Y;

	m_peanut = new Surface(PIC_DASHBOARD_R + "peanut.png");
}


void Dashboard::draw_dashboard(Camera *camera)
{
	/*
		Affichage des vies
	*/
	if (gPlayers->local_player()->HP() < 0)
		return;
	for (int i = 0; i < gPlayers->local_player()->HP(); i++) {
		camera->display_picture(m_heart, &m_HP_pos, true);
		m_HP_pos.x += 30;
	}
	m_HP_pos.x -= gPlayers->local_player()->HP() * 30;

	/*
		Affichage de l'arme et des munitions
	*/
	camera->display_picture(m_weapons_pictures[gPlayers->local_player()->type_of_weapon()], &m_weapons_pos, true);
	Rect pos_munitions;
    std::ostringstream ossmun;
    ossmun <<  "x " << gPlayers->local_player()->munitions();
    std::string munitions = ossmun.str();
	Surface_text *munitions_picture = new Surface_text(munitions, m_font);
	pos_munitions.x = POS_WEAPON_X + m_weapons_pictures[gPlayers->local_player()->type_of_weapon()]->w() + 10;
	pos_munitions.y = m_weapons_pos.y + (m_weapons_pictures[gPlayers->local_player()->type_of_weapon()]->h() - munitions_picture->h())/2;
	camera->display_picture(munitions_picture, &pos_munitions, true);
	delete munitions_picture;


	/*
		Affichage des cacahuetes
	*/
	Rect pos_peanut;
	Rect pos_peanuts_number;
	std::ostringstream osspeanut;
	osspeanut << "x " << gPlayers->local_player()->peanuts();
	std::string peanuts_number = osspeanut.str();
	Surface_text *peanuts_number_picture = new Surface_text(peanuts_number, m_font);
	Rect pos_camera = camera->frame();
	pos_peanuts_number.x = pos_camera.w - peanuts_number_picture->w() - 30;
	pos_peanuts_number.y = 30;
	pos_peanut.x = pos_peanuts_number.x - DASH_DECALAGE - m_peanut->w();
	pos_peanut.y = pos_peanuts_number.y + (peanuts_number_picture->w() - m_peanut->w()) / 2;
	camera->display_picture(peanuts_number_picture, &pos_peanuts_number, true);
	camera->display_picture(m_peanut, &pos_peanut, true);
	delete peanuts_number_picture;

	/* affichage de l'alert */
	if ( m_alert ) {
        Rect pos_alert;
        pos_alert.x = WINDOW_HEIGHT/2;
        pos_alert.y = WINDOW_WIDTH/2;
        Surface * img_alert = m_alert->curr_pic();
        /* je sais pas trop pq il y a besoin d'un offset ici... */
        pos_alert.x -= img_alert->w()/2-100;
        pos_alert.y -= img_alert->h()/2+100;
        camera->display_picture(img_alert,&pos_alert,true);
	}
}

void Dashboard::alert(std::string text)
{
    if ( m_alert ) {
        delete m_alert;
    }
    m_alert = new Anim_text(text, 150, 10, 30);
}

void Dashboard::update()
{
    if ( m_alert ) {
        if ( m_alert->deletable() ) {
            delete m_alert;
            m_alert = NULL;
        } else {
            m_alert->next_pic();
        }
    }
}

void Dashboard::clear_dashboard()
{
	if (m_weapons_pictures) {
		for (int i = 0; i < LASTWEAPON; i++)
			if (m_weapons_pictures[i])
				delete m_weapons_pictures[i];
		delete[] m_weapons_pictures;
		m_weapons_pictures = NULL;
	}
	if (m_heart)
		delete m_heart;
	m_heart = NULL;
	if (m_peanut)
		delete m_peanut;
	m_peanut = NULL;

	if ( m_alert ) {
        delete m_alert;
        m_alert = NULL;
    }

    delete m_alert;
}
