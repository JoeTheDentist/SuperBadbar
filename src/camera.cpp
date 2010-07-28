#include <iostream>#include <SDL/SDL.h>#include <stdint.h>#include "camera.h"#include "globals.h"Camera::Camera(){}Camera::Camera(Sprite *target){	m_target = target;	m_frame.h = window_height;	m_frame.w = window_weight;}Camera::~Camera(){}void Camera::update_pos(){	SDL_Rect position_target = m_target->position();	m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);	m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);	if (m_frame.x < 0)		m_frame.x = 0;	if (m_frame.y < 0)		m_frame.y = 0;	if ((uint32_t) (m_frame.x + m_frame.w) > level_weight)		m_frame.x = level_weight - m_frame.w;	if ((uint32_t) (m_frame.y + m_frame.h) > level_height)		m_frame.y = level_height - m_frame.h;}

void Camera::display_sprite(Babar *babar)
{
	SDL_Rect pos_babar = babar->position();
	pos_babar.x -= m_frame.x;
	pos_babar.y -= m_frame.y;
	SDL_BlitSurface(babar->current_picture(), NULL, screen, &pos_babar);

}
void Camera::display_sprite(Monster *monster)
{
	SDL_Rect pos_monster = monster->position();
	pos_monster.x -= m_frame.x;
	pos_monster.y -= m_frame.y;
	SDL_BlitSurface(monster->current_picture(), NULL, screen, &pos_monster);

}

SDL_Rect Camera::frame(){	return m_frame;}
