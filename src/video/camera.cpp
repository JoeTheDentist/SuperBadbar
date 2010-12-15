#include <iostream>#include <SDL/SDL.h>#include <stdint.h>#include "camera.h"#include "../util/debug.h"#include "../sprites/sprites.h"#include "../sprites/babar.h"#include "../sprites/monsters.h"#include "../sprites/projectiles.h"#include "../video/statics.h"#include "../game/static_data.h"#include "../util/globals.h"#include "../events/events_manager.h"#include "../events/events.h"Camera::Camera(){	m_target = NULL;	m_screen = NULL;	m_decalage.x = 0;	m_decalage.y = 0;	m_direction.x = 0;	m_direction.y = 0;}Camera::~Camera(){	PRINT_CONSTR(1, "Destruction de la camera")	PRINT_TRACE(1, "Fermeture de la fenetre")	SDL_FreeSurface(m_screen);}void Camera::init_camera(Sprite *target){
    Rect pos_temp = target->position();	SDL_Rect position_target;
	position_target.x = pos_temp.x;
	position_target.y = pos_temp.y;
	position_target.h = pos_temp.h;
	position_target.w = pos_temp.w;	PRINT_CONSTR(1, "Construction de la camera")	PRINT_TRACE(1, "Initialisation de la SDL")	if (SDL_Init(SDL_INIT_VIDEO) == -1) {		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")		return;	}	m_frame.h = WINDOW_HEIGHT;	m_frame.w = WINDOW_WEIGHT;	m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);	m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);	PRINT_TRACE(1, "Ouverture de la fenetre (de taille %d*%d)", m_frame.h, m_frame.w)	m_screen = SDL_SetVideoMode(m_frame.w, m_frame.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);	SDL_WM_SetCaption("SuperBabar", NULL);	m_target = target;}void Camera::update_decalage(){	//mise à jour de la direction du decalage	if (m_target->direction_h() != 0) {		m_direction.x = m_target->direction_h();	}	/* del vertical
	if (m_target->direction_v() != 0) {		m_direction.y = m_target->direction_v();	}*/	// gestion du decalage horizontal	m_decalage.x += m_direction.x* VITESSE_DECALAGE_CAMERA;	if (m_decalage.x < -m_frame.w *MAX_DECALAGE_CAMERA)		m_decalage.x = -m_frame.w * MAX_DECALAGE_CAMERA;	if (m_decalage.x > m_frame.w * MAX_DECALAGE_CAMERA)		m_decalage.x = m_frame.w * MAX_DECALAGE_CAMERA;	// gestion du decalage vertical	/* del vertical
	if(m_target->direction_v() == 0) {		if (m_decalage.y > 0) {			if (m_decalage.y < VITESSE_DECALAGE_RETOUR_CAMERA)				m_decalage.y = 0;			else				m_decalage.y -= VITESSE_DECALAGE_RETOUR_CAMERA;		} else {			if (m_decalage.y > -VITESSE_DECALAGE_RETOUR_CAMERA)				m_decalage.y = 0;			else				m_decalage.y += VITESSE_DECALAGE_RETOUR_CAMERA;		}	} else {		m_decalage.y += (m_target)->direction_v()* VITESSE_DECALAGE_CAMERA;		if (m_decalage.y < -m_frame.h *MAX_DECALAGE_CAMERA)			m_decalage.y = -m_frame.h * MAX_DECALAGE_CAMERA;		if (m_decalage.y > m_frame.h * MAX_DECALAGE_CAMERA)			m_decalage.y = m_frame.h * MAX_DECALAGE_CAMERA;	}*/}                                     void Camera::update_pos(Static_data *static_data){	update_decalage();
	Rect pos_temp = m_target->position();
	SDL_Rect position_target;
	position_target.x = pos_temp.x;
	position_target.y = pos_temp.y;
	position_target.h = pos_temp.h;
	position_target.w = pos_temp.w;	m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);	m_frame.x += m_decalage.x;	m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);	m_frame.y += m_decalage.y;	if (m_frame.x < 0)		m_frame.x = 0;	if (m_frame.y < 0)		m_frame.y = 0;	if ((uint32_t) (m_frame.x + m_frame.w) > static_data->static_data_weight())		m_frame.x = static_data->static_data_weight() - m_frame.w;	if ((uint32_t) (m_frame.y + m_frame.h) > static_data->static_data_height())		m_frame.y = static_data->static_data_height() - m_frame.h;}
void Camera::display_background(SDL_Surface *background) {	SDL_Rect pos;	//~ pos = m_target->position();	//~ pos.x = -pos.x * BACKGROUND_SPEED;	//~ pos.y = -pos.y * BACKGROUND_SPEED;	pos.x = - m_frame.x  * BACKGROUND_SPEED;	pos.y = - m_frame.y * BACKGROUND_SPEED;	SDL_BlitSurface(background, NULL, m_screen, &pos);}void Camera::display_sprite(const Sprite *sprite) const{	SDL_Surface *picture = sprite->current_picture();	if (picture != NULL) {
		Rect pos_temp = sprite->position();
        SDL_Rect pos_sprite;
        pos_sprite.x = pos_temp.x;
        pos_sprite.y = pos_temp.y;
        pos_sprite.h = pos_temp.h;
        pos_sprite.w = pos_temp.w;		pos_sprite.x -= m_frame.x;		pos_sprite.y -= m_frame.y;		SDL_BlitSurface(picture, NULL, m_screen, &pos_sprite);	}}
void Camera::display_static(Static *sttc) 
{
    Rect pos_temp = sttc->position();
	SDL_Rect pos_static;
	pos_static.x = pos_temp.x;
	pos_static.y = pos_temp.y;
	pos_static.h = pos_temp.h;
	pos_static.w = pos_temp.w;
    pos_static.x -= m_frame.x;
	pos_static.y -= m_frame.y;
    SDL_BlitSurface(sttc->image(), NULL, m_screen, &pos_static);
}
void Camera::display_events(Events_manager * const event_manager) const{	event_manager->display_events((Camera *const)this);}
void Camera::display_event(Event *event){	SDL_Surface *picture = event->current_picture();	if (picture != NULL) {
		Rect pos_temp = event->current_pos();
        SDL_Rect pos_event;
        pos_event.x = (int)pos_temp.x;
        pos_event.y = (int)pos_temp.y;
        pos_event.h = (unsigned int)pos_temp.h;
        pos_event.w = (unsigned int)pos_temp.w;		pos_event.x -= m_frame.x;		pos_event.y -= m_frame.y;		SDL_BlitSurface(picture, NULL, m_screen, &pos_event);	}}Rect Camera::frame() const{
    Rect pos_temp;
    pos_temp.x = m_frame.x;
    pos_temp.y = m_frame.y;
    pos_temp.h = m_frame.h;
    pos_temp.w = m_frame.w;	return pos_temp;}void Camera::display_picture(SDL_Surface *pic, Rect *pos){
    SDL_Rect * pos_sdl = new SDL_Rect;
    pos_sdl->x = (int)pos->x;
    pos_sdl->y = (int)pos->y;
    pos_sdl->h = (unsigned int)pos->h;
    pos_sdl->w = (unsigned int)pos->w;	SDL_BlitSurface(pic, NULL, m_screen, pos_sdl);	delete pos_sdl;}
void Camera::flip_camera(){	SDL_Flip(m_screen);}