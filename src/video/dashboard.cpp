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

#include "../../lib/SDL/include/SDL/SDL_ttf.h"


#include "dashboard.h"
#include "../video/camera.h"
#include "../util/debug.h"
#include "../sprites/babar.h"
#include "../video/talks.h"
#include "../video/surface.h"
#include "../video/pictures_container.h"
#include "../util/globals.h"



Dashboard::Dashboard():
	m_font(NULL),
	m_heart(NULL),
	m_weapons_pictures(NULL),
	m_peanut(NULL)
{
	PRINT_CONSTR(1, "Construction de Dashboard (tableau de bord)")
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
	std::string font_name = "font1.ttf";
	m_font = TTF_OpenFont((rac + FONTS_TALKS_DIR + font_name).c_str(), 30);
	m_font_color.r = 255;
	m_font_color.g = 255;
	m_font_color.b = 255;

	m_heart = new Surface(rac+"/pic/dashboard/heart.png");
	m_lifes_pos.x = POS_HEART_X;
	m_lifes_pos.y = POS_HEART_Y;

	m_weapons_pictures = new Surface*[SHOTGUN + 1];
	m_weapons_pictures[MACHINEGUN] = new Surface(PIC_DASHBOARD_R + "weapon/machinegun.png");
	m_weapons_pictures[GUN] = new Surface(PIC_DASHBOARD_R + "weapon/gun.png");
	m_weapons_pictures[SHOTGUN] = new Surface(PIC_DASHBOARD_R + "weapon/shotgun.png");
	m_weapons_pos.x = POS_WEAPON_X;
	m_weapons_pos.y = POS_WEAPON_Y;
	
	m_peanut = new Surface(PIC_DASHBOARD_R + "peanut.png");
}


void Dashboard::draw_dashboard(int lifes, Camera *camera)
{
	/*
		Affichage des vies
	*/
	if (lifes < 0)
		return;
	for (int i = 0; i < lifes; i++) {
		camera->display_picture(m_heart, &m_lifes_pos, true);
		m_lifes_pos.x += 30;
	}
	m_lifes_pos.x -= lifes * 30;

	/*
		Affichage de l'arme et des munitions
	*/
	camera->display_picture(m_weapons_pictures[gBabar->type_of_weapon()], &m_weapons_pos, true);
	Rect pos_munitions;
	SDL_Surface *munitions_pictures = NULL;
	char munitions[5];
	sprintf(munitions, "x %d", gBabar->munitions());
	munitions_pictures = TTF_RenderText_Blended(m_font, munitions, m_font_color);
	pos_munitions.x = POS_WEAPON_X + m_weapons_pictures[gBabar->type_of_weapon()]->w() + 10;
	pos_munitions.y = m_weapons_pos.y + (m_weapons_pictures[gBabar->type_of_weapon()]->h() - munitions_pictures->h)/2;
	camera->display_picture(munitions_pictures, &pos_munitions);
	SDL_FreeSurface(munitions_pictures);
	
	/*
		Affichage des cacahuetes
	*/
	Rect pos_peanut;
	Rect pos_peanuts_number;
	char peanuts_number[5];
	SDL_Surface *peanuts_number_picture = NULL;
	sprintf(peanuts_number, "x %d", gBabar->peanuts());
	peanuts_number_picture = TTF_RenderText_Blended(m_font, peanuts_number, m_font_color);
	Rect pos_camera = camera->frame();
	pos_peanuts_number.x = pos_camera.w - peanuts_number_picture->w - 30;
	pos_peanuts_number.y = 30;
	pos_peanut.x = pos_peanuts_number.x - DASH_DECALAGE - m_peanut->w();
	pos_peanut.y = pos_peanuts_number.y + (peanuts_number_picture->w - m_peanut->w()) / 2;
	camera->display_picture(peanuts_number_picture, &pos_peanuts_number);
	camera->display_picture(m_peanut, &pos_peanut, true);
	SDL_FreeSurface(peanuts_number_picture);
}

void Dashboard::clear_dashboard()
{
	if (m_weapons_pictures) {
		for (int i = 0; i < SHOTGUN + 1; i++)
			if (m_weapons_pictures[i])
				delete m_weapons_pictures[i];
		delete[] m_weapons_pictures;
		m_weapons_pictures = NULL;
	}
	if (m_heart)
		delete m_heart;
	m_heart = NULL;
	if (m_font)
		TTF_CloseFont(m_font);
	m_font = NULL;
	if (m_peanut)
		delete m_peanut;
	m_peanut = NULL;

}
