#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <SDL/SDL_ttf.h>


#include "dashboard.h"
#include "../video/camera.h"
#include "../util/debug.h"
#include "../sprites/babar.h"
#include "../video/talks.h"
#include "../util/globals.h"



Dashboard::Dashboard()
{
    std::string rac = RAC;
	std::string font_name = "font1.ttf";
	m_font = TTF_OpenFont((rac + FONTS_TALKS_DIR + font_name).c_str(), 30);
	m_font_color.r = 255;
	m_font_color.g = 255;
	m_font_color.b = 255;

	m_heart = SDL_LoadBMP((rac+"/pic/dashboard/heart.bmp").c_str());
	SDL_SetColorKey(m_heart, SDL_SRCCOLORKEY, SDL_MapRGB(m_heart->format, 0, 0, 255));
	m_lifes_pos.x = POS_HEART_X;
	m_lifes_pos.y = POS_HEART_Y;

	m_weapons_pictures = new SDL_Surface*[SHOTGUN + 1];
	m_weapons_pictures[MACHINEGUN] = SDL_LoadBMP((rac+"/pic/dashboard/heart.bmp").c_str());
	m_weapons_pictures[GUN] = SDL_LoadBMP((rac+"/pic/statics/black_board.bmp").c_str());
	m_weapons_pictures[SHOTGUN] = SDL_LoadBMP((rac+"/pic/dashboard/heart.bmp").c_str());
	for (int i = 0; i < SHOTGUN + 1; i++)
		SDL_SetColorKey(m_weapons_pictures[i], SDL_SRCCOLORKEY, SDL_MapRGB(m_weapons_pictures[i]->format, 0, 0, 255));
	m_weapons_pos.x = POS_WEAPON_X;
	m_weapons_pos.y = POS_WEAPON_Y;


}


Dashboard::~Dashboard()
{
	SDL_FreeSurface(m_heart);
}


void Dashboard::draw_dashboard(int lifes, Camera *camera, Babar *babar)
{
	if (lifes < 0)
		return;
	for (int i = 0; i < lifes; i++) {
		camera->display_picture(m_heart, &m_lifes_pos);
		m_lifes_pos.x += 30;
	}
	m_lifes_pos.x -= lifes * 30;

	camera->display_picture(m_weapons_pictures[babar->type_of_weapon()], &m_weapons_pos);
	Rect pos_munitions;
	SDL_Surface *munitions_pictures = NULL;
	char munitions[5];
	sprintf(munitions, "x %d", babar->munitions());
	munitions_pictures = TTF_RenderText_Blended(m_font, munitions, m_font_color);
	pos_munitions.x = POS_WEAPON_X + m_weapons_pictures[babar->type_of_weapon()]->w + 10;
	pos_munitions.y = m_weapons_pos.y + (m_weapons_pictures[babar->type_of_weapon()]->h - munitions_pictures->h)/2;
	camera->display_picture(munitions_pictures, &pos_munitions);
	SDL_FreeSurface(munitions_pictures);

}
