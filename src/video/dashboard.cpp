#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "dashboard.h"
#include "../video/camera.h"
#include "../util/debug.h"
     

Dashboard::Dashboard()
{
	m_heart = SDL_LoadBMP("../pic/dashboard/heart.bmp");
	SDL_SetColorKey(m_heart, SDL_SRCCOLORKEY, SDL_MapRGB(m_heart->format, 0, 0, 255));
	m_lifes_pos.x = POS_HEART_X;
	m_lifes_pos.y = POS_HEART_Y;
}


Dashboard::~Dashboard()
{
	SDL_FreeSurface(m_heart);
}


void Dashboard::draw_dashboard(int lifes, Camera *camera)
{
	if (lifes < 0) 
		return;
	for (int i = 0; i < lifes; i++) {
		camera->display_picture(m_heart, &m_lifes_pos);
		m_lifes_pos.x += 30;
	}
	m_lifes_pos.x -= lifes * 30;
		
}
