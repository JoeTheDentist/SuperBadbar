#include <iostream>#include <SDL/SDL.h>#include <stdint.h>#include "camera.h"#include "debug.h"#include "globals.h"Camera::Camera(){	PRINT_CONSTR(1, "Construction de la camera")}Camera::Camera(Sprite *target){			PRINT_CONSTR(1, "Construction de la camera")	m_target = target;	m_frame.h = window_height;	m_frame.w = window_weight;}Camera::~Camera(){	PRINT_CONSTR(1, "Destruction de la camera")}void Camera::update_pos(){	SDL_Rect position_target = m_target->position();	m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);	m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);	if (m_frame.x < 0)		m_frame.x = 0;	if (m_frame.y < 0)		m_frame.y = 0;	if ((uint32_t) (m_frame.x + m_frame.w) > curr_lvl.level_weight())		m_frame.x = curr_lvl.level_weight() - m_frame.w;	if ((uint32_t) (m_frame.y + m_frame.h) > curr_lvl.level_height())		m_frame.y = curr_lvl.level_height() - m_frame.h;}
void Camera::display_background(SDL_Surface *background){	SDL_Rect pos;	pos = m_target->position();	pos.x = -pos.x * BACKGROUND_SPEED;	pos.y = -pos.y * BACKGROUND_SPEED;		//~ pos.x = - m_frame.x  * BACKGROUND_SPEED;	//~ pos.y = - m_frame.y * BACKGROUND_SPEED;	SDL_BlitSurface(background, NULL, screen, &pos);}
void Camera::display_sprite(Babar *babar)
{
	SDL_Rect pos_babar = babar->position();
	pos_babar.x -= m_frame.x;
	pos_babar.y -= m_frame.y;
	SDL_BlitSurface(babar->current_picture(), NULL, screen, &pos_babar);

}
void Camera::display_sprite(Monster *monster)   /* Surcharge car les current_picture appartiennent au classe filles, on pourrait faire une template à la place */
{
	SDL_Rect pos_monster = monster->position();
	pos_monster.x -= m_frame.x;
	pos_monster.y -= m_frame.y;
	SDL_BlitSurface(monster->current_picture(), NULL, screen, &pos_monster);
}

void Camera::display_sprite(Projectile * proj)   /* Surcharge */
{
	SDL_Rect pos_proj = proj->position();
	pos_proj.x -= m_frame.x;
	pos_proj.y -= m_frame.y;
	SDL_BlitSurface(proj->current_picture(), NULL, screen, &pos_proj);
}

void Camera::display_static(Static *sttc)
{
    SDL_Rect pos_static = sttc->position();
    pos_static.x -= m_frame.x;
	pos_static.y -= m_frame.y;
    SDL_BlitSurface(sttc->image(), NULL, screen, &pos_static);
}

SDL_Rect Camera::frame(){	return m_frame;}
