/**
 * 	@file dashboard.cpp
 * 	@brief Implémentation de la classe Dashboard
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "Dashboard.h"

#include <sstream>

#include <items/Weapon.h>

#include "actors/Babar.h"
#include <param/param_dashboard.h>
#include "players/PlayersManager.h"
#include "util/utils.h"
#include <video/AnimText.h>
#include "video/Camera.h"
#include <video/LifeBarPossessor.h>
#include <video/PicturesContainer.h>
#include "video/Surface.h"
#include <video/SurfaceFrame.h>
#include <video/SurfaceUniform.h>
#include "video/SurfaceText.h"
#include "video/Talks.h"
#include "util/globals.h"


Dashboard::Dashboard():
	m_heart(NULL),
	m_weapons_pictures(NULL),
	m_peanut(NULL),
	m_babar_head(NULL),
	m_sizeFont(DASH_TEXT_SIZE),
	m_rFont(DASH_TEXT_R),
	m_gFont(DASH_TEXT_G),
	m_bFont(DASH_TEXT_B),
	m_nameFont(DASH_TEXT_FONT),
	m_alert(NULL),
	m_life_bar_possessor(NULL),
	m_green_rect(NULL),
	m_red_rect(NULL),
	m_life_bar(NULL)
{
	PRINT_CONSTR(1, "Construction de Dashboard (tableau de bord)")
	// Abonnement aux life_bar_possessors
	LifeBarPossessor::setDashboard(this);
}

Dashboard::~Dashboard()
{
	clear_dashboard();
	PRINT_CONSTR(1, "Destruction de Dashboard")
}

void Dashboard::init_dashboard(PicturesContainer *)
{
	#ifndef DISABLE_DASHBOARD
	clear_dashboard();
    std::string rac = RACINE_R;
	m_heart = new Surface(PIC_DASHBOARD_R + "heart.png");
	m_babar_head = new Surface(PIC_DASHBOARD_R + "babarhead.png");

	m_HP_pos.x = POS_HEART_X;
	m_HP_pos.y = POS_HEART_Y;
	m_weapons_pictures = new Surface*[LASTWEAPON];
	for (int i = 0; i < LASTWEAPON; i++)
		m_weapons_pictures[i] = NULL;
	m_weapons_pictures[MACHINE_GUN] = new Surface(PIC_DASHBOARD_R + "weapon/machinegun.png");
	m_weapons_pictures[ELMAR_MACHINE_GUN] = new Surface(PIC_DASHBOARD_R + "weapon/elmar_machine_gun.png");
	m_weapons_pictures[GUN] = new Surface(PIC_DASHBOARD_R + "weapon/gun.png");
	m_weapons_pictures[SHOTGUN] = new Surface(PIC_DASHBOARD_R + "weapon/shotgun.png");
	m_weapons_pictures[ROCKET_LAUNCHER] = new Surface(PIC_DASHBOARD_R + "weapon/rocket_launcher.png");
	m_weapons_pos.x = POS_WEAPON_X;
	m_weapons_pos.y = POS_WEAPON_Y;
	m_peanut = new Surface(PIC_DASHBOARD_R + "peanut.png");
	m_green_rect = new SurfaceUniform(LIFE_BAR_W, LIFE_BAR_H, 0, 255, 0);
	m_red_rect = new SurfaceUniform(LIFE_BAR_W, LIFE_BAR_H, 255, 0, 0);
	m_life_bar = new SurfaceUniform(LIFE_BAR_W, LIFE_BAR_H, 0, 255, 0);
	m_frame_life_bar.x = Constants::WINDOW_WIDTH - m_life_bar->w() - 20;
	m_frame_life_bar.y = Constants::WINDOW_HEIGHT -100 - DASH_DECALAGE;
	m_frame_life_bar.w = m_life_bar->w();
	m_frame_life_bar.h = m_life_bar->h();
	m_rect_null.x = 0;
	m_rect_null.y = 0;
	m_rect_null.w = 0;
	m_rect_null.h = 0;
	#endif
}

void Dashboard::draw_dashboard(Camera *camera)
{
	#ifndef DISABLE_DASHBOARD
	/********************************************************************************/
	/*	HP																VIES		*/
	/*	ARME															CACAHUETTES	*/
	/*																				*/
	/*																				*/
	/*								ALERT											*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																				*/
	/*																status_bar		*/
	/********************************************************************************/

	Rect pos_camera = camera->frame();

	/*
		Affichage des hp
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
	SurfaceText *munitions_picture = new SurfaceText(munitions, m_sizeFont, m_rFont, m_gFont, m_bFont, m_nameFont);
	pos_munitions.x = POS_WEAPON_X + m_weapons_pictures[gPlayers->local_player()->type_of_weapon()]->w() + 10;
	pos_munitions.y = m_weapons_pos.y + (m_weapons_pictures[gPlayers->local_player()->type_of_weapon()]->h() - munitions_picture->h())/2;
	camera->display_picture(munitions_picture, &pos_munitions, true);
	delete munitions_picture;


	/*
		Affichage des vies
	*/
	Rect pos_lifes;
	Rect pos_text_lifes;
	std::ostringstream osslifes;
	osslifes << "x " << gPlayers->local_player()->lifes();
	SurfaceText *lifes_number_picture = new SurfaceText(osslifes.str());
	pos_text_lifes.x = pos_camera.w - lifes_number_picture->w() - 30;
	pos_lifes.x = pos_text_lifes.x - DASH_DECALAGE - m_babar_head->w();
	pos_lifes.y = 30;
	pos_text_lifes.y = pos_lifes.y - (lifes_number_picture->h() - m_babar_head->h()) / 2;
	camera->display_picture(lifes_number_picture, & pos_text_lifes, true);
	camera->display_picture(m_babar_head, &pos_lifes, true);
	delete lifes_number_picture;


	/*
		Affichage des cacahuetes
	*/
	Rect pos_peanut;
	Rect pos_peanuts_number;
	std::ostringstream osspeanut;
	osspeanut << "x " << gPlayers->local_player()->peanuts();
	std::string peanuts_number = osspeanut.str();
	SurfaceText *peanuts_number_picture = new SurfaceText(peanuts_number,  m_sizeFont, m_rFont, m_gFont, m_bFont, m_nameFont);
	pos_peanuts_number.x = pos_camera.w - peanuts_number_picture->w() - 30;
	pos_peanut.x = pos_peanuts_number.x - DASH_DECALAGE - m_peanut->w();
	pos_peanut.y = DASH_DECALAGE + pos_lifes.y + m_babar_head->h();
	pos_peanuts_number.y = pos_peanut.y - (peanuts_number_picture->h() - m_peanut->h()) / 2;

	camera->display_picture(peanuts_number_picture, &pos_peanuts_number, true);
	camera->display_picture(m_peanut, &pos_peanut, true);
	delete peanuts_number_picture;


	/* affichage de l'alert */
	if ( m_alert ) {
        Rect pos_alert;
        pos_alert.x = Constants::WINDOW_HEIGHT/2;
        pos_alert.y = Constants::WINDOW_WIDTH/2;
        Surface * img_alert = m_alert->curr_pic();
        /* je sais pas trop pq il y a besoin d'un offset ici... */
        pos_alert.x -= img_alert->w()/2-100;
        pos_alert.y -= img_alert->h()/2+100;
        camera->display_picture(img_alert,&pos_alert,true);
	}

	/* affichage de le life bar */
	if (m_life_bar_possessor) {
		Rect rect1;
		rect1.x = 0;
		rect1.y = 0;
		rect1.w = m_life_bar->w();
		rect1.h = m_life_bar->h();
		m_green_rect->blit_surface(m_life_bar, rect1, rect1);
		rect1.x = double(m_life_bar->w()) * m_life_bar_possessor->life_bar_status();
		m_red_rect->blit_surface(m_life_bar, rect1, rect1);
		camera->display_picture(m_life_bar, &m_frame_life_bar, true);
	}

	#endif
}

void Dashboard::alert(std::string text)
{
	#ifndef DISABLE_DASHBOARD
    if ( m_alert ) {
        delete m_alert;
    }
    m_alert = new AnimText(text, 150, 10, 30);
	#endif
}

void Dashboard::update()
{
	#ifndef DISABLE_DASHBOARD
    if ( m_alert ) {
        if ( m_alert->deletable() ) {
            delete m_alert;
            m_alert = NULL;
        } else {
            m_alert->next_pic();
        }
    }
	#endif
}

void Dashboard::clear_dashboard()
{
	if (m_weapons_pictures) {
		for (int i = 0; i < LASTWEAPON; i++)
			delete m_weapons_pictures[i];
		delete[] m_weapons_pictures;
		m_weapons_pictures = NULL;
	}
	delete m_heart;
	m_heart = NULL;
	delete m_peanut;
	m_peanut = NULL;
	delete m_alert;
	m_alert = NULL;
	delete m_babar_head;
	m_babar_head = NULL;
	delete m_green_rect;
	m_green_rect = NULL;
	delete m_red_rect;
	m_green_rect = NULL;
	delete m_life_bar;
	m_life_bar = NULL;
}
