#include <iostream>#include <SDL/SDL.h>#include <stdint.h>#include "camera.h"#include "debug.h"#include "sprites.h"#include "statics.h"#include "static_data.h"#include "globals.h"Camera::Camera(Sprite *target){			PRINT_CONSTR(1, "Construction de la camera")	PRINT_TRACE(1, "Initialisation de la SDL")		if (SDL_Init(SDL_INIT_VIDEO) == -1) {		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")		return;	}		m_frame.h = WINDOW_HEIGHT;	m_frame.w = WINDOW_WEIGHT;	PRINT_TRACE(1, "Ouverture de la fenetre (de taille %d*%d)", m_frame.h, m_frame.w)	m_screen = SDL_SetVideoMode(m_frame.w, m_frame.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);	SDL_WM_SetCaption("SuperBabar", NULL);	m_target = target;}Camera::~Camera(){	PRINT_CONSTR(1, "Destruction de la camera")	PRINT_TRACE(1, "Fermeture de la fenetre")	SDL_FreeSurface(m_screen);	PRINT_TRACE(1, "Fermeture de la SDL")	SDL_Quit();}void Camera::update_pos(Static_data *static_data){	SDL_Rect position_target = m_target->position();	m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);	m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);	if (m_frame.x < 0)		m_frame.x = 0;	if (m_frame.y < 0)		m_frame.y = 0;	if ((uint32_t) (m_frame.x + m_frame.w) > static_data->static_data_weight())		m_frame.x = static_data->static_data_weight() - m_frame.w;	if ((uint32_t) (m_frame.y + m_frame.h) > static_data->static_data_height())		m_frame.y = static_data->static_data_height() - m_frame.h;	PRINT_DEBUG(1, "%d", m_frame.y)}
void Camera::display_background(SDL_Surface *background){	SDL_Rect pos;	//~ pos = m_target->position();	//~ pos.x = -pos.x * BACKGROUND_SPEED;	//~ pos.y = -pos.y * BACKGROUND_SPEED;	pos.x = - m_frame.x  * BACKGROUND_SPEED;	pos.y = - m_frame.y * BACKGROUND_SPEED;	SDL_BlitSurface(background, NULL, m_screen, &pos);}
void Camera::display_sprite(Babar *babar)
{
	SDL_Rect pos_babar = babar->position();
	pos_babar.x -= m_frame.x;
	pos_babar.y -= m_frame.y;
	SDL_BlitSurface(babar->current_picture(), NULL, m_screen, &pos_babar);

}
void Camera::display_sprite(Monster *monster)   /* Surcharge car les current_picture appartiennent au classe filles, on pourrait faire une template � la place */
{
	SDL_Rect pos_monster = monster->position();
	pos_monster.x -= m_frame.x;
	pos_monster.y -= m_frame.y;
	SDL_BlitSurface(monster->current_picture(), NULL, m_screen, &pos_monster);
}

void Camera::display_sprite(Projectile * proj)   /* Surcharge */
{
	SDL_Rect pos_proj = proj->position();
	pos_proj.x -= m_frame.x;
	pos_proj.y -= m_frame.y;
	SDL_BlitSurface(proj->current_picture(), NULL, m_screen, &pos_proj);
}

void Camera::display_static(Static *sttc)
{
    SDL_Rect pos_static = sttc->position();
    pos_static.x -= m_frame.x;
	pos_static.y -= m_frame.y;
    SDL_BlitSurface(sttc->image(), NULL, m_screen, &pos_static);
}

SDL_Rect Camera::frame(){	return m_frame;}void Camera::display_picture(SDL_Surface *pic, SDL_Rect *pos){	SDL_BlitSurface(pic, NULL, m_screen, pos);}
void Camera::flip_camera(){	SDL_Flip(m_screen);}