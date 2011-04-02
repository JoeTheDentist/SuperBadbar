/** * 	@file camera.cpp * 	@brief Implémentation de la classe Camera * * 	@author Guillaume Bérard & Benoit Morel * 	@date decembre 2010 * */#include <iostream>#include <stdint.h>#include "camera.h"#include "../util/debug.h"#include "../sprites/sprites.h"#include "../sprites/babar.h"#include "../sprites/monsters.h"#include "../sprites/projectiles.h"#include "../video/statics.h"#include "../video/surface.h"#include "../video/displayable.h"#include "../game/static_data.h"#include "../events/events_manager.h"#include "../events/events.h"#include "../physic/collisions_manager.h"#include "../physic/moving_platform.h"#include "../util/globals.h"#include "../util/repertories.h"
Camera::Camera(){	m_target = NULL;	m_screen = NULL;	m_decalage.x = 0;	m_decalage.y = 0;	m_direction.x = 0;	m_direction.y = 0;}Camera::~Camera(){	PRINT_CONSTR(1, "Destruction de la camera")	PRINT_TRACE(1, "Fermeture de la fenetre")	SDL_FreeSurface(m_screen);}void Camera::init_camera(Sprite *target){	m_frame.x = 0;	m_frame.y = 0;	if (target) {		set_target(target);	}
	PRINT_CONSTR(1, "Construction de la camera")	m_frame.h = WINDOW_HEIGHT;	m_frame.w = WINDOW_WEIGHT;	PRINT_TRACE(1, "Ouverture de la fenetre (de taille %d*%d)", m_frame.h, m_frame.w)	m_screen = SDL_SetVideoMode(m_frame.w, m_frame.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);	SDL_WM_SetCaption("SuperBabar", NULL);	m_target = target;	#ifdef DEBUG_COLL	m_green_coll = new Surface(PIC_DEBUG_R + "green_col.png");	m_red_coll = new Surface(PIC_DEBUG_R + "red_col.png");	#endif}void Camera::set_target(Sprite *target) {    Rect pos_temp = target->position();	SDL_Rect position_target;	position_target.x = pos_temp.x;	position_target.y = pos_temp.y;	position_target.h = pos_temp.h;	position_target.w = pos_temp.w;	m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);	m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);	m_target = target;	}void Camera::update_decalage(){	//mise à jour de la direction du decalage	if (m_target->direction_h() != 0) {		m_direction.x = m_target->direction_h();	}	/* del vertical
	if (m_target->direction_v() != 0) {		m_direction.y = m_target->direction_v();	}*/	// gestion du decalage direction	m_decalage.x += m_direction.x* VITESSE_DECALAGE_CAMERA;	if (m_decalage.x < -m_frame.w *MAX_DECALAGE_CAMERA)		m_decalage.x = -m_frame.w * MAX_DECALAGE_CAMERA;	if (m_decalage.x > m_frame.w * MAX_DECALAGE_CAMERA)		m_decalage.x = m_frame.w * MAX_DECALAGE_CAMERA;	// gestion du decalage vertical	/* del vertical
	if(m_target->direction_v() == 0) {		if (m_decalage.y > 0) {			if (m_decalage.y < VITESSE_DECALAGE_RETOUR_CAMERA)				m_decalage.y = 0;			else				m_decalage.y -= VITESSE_DECALAGE_RETOUR_CAMERA;		} else {			if (m_decalage.y > -VITESSE_DECALAGE_RETOUR_CAMERA)				m_decalage.y = 0;			else				m_decalage.y += VITESSE_DECALAGE_RETOUR_CAMERA;		}	} else {		m_decalage.y += (m_target)->direction_v()* VITESSE_DECALAGE_CAMERA;		if (m_decalage.y < -m_frame.h *MAX_DECALAGE_CAMERA)			m_decalage.y = -m_frame.h * MAX_DECALAGE_CAMERA;		if (m_decalage.y > m_frame.h * MAX_DECALAGE_CAMERA)			m_decalage.y = m_frame.h * MAX_DECALAGE_CAMERA;	}*/}void Camera::update_pos(){	update_decalage();
	Rect pos_temp = m_target->position();	std::cout << pos_temp.x << " " << pos_temp.y << std::endl;
	SDL_Rect position_target;
	position_target.x = pos_temp.x;
	position_target.y = pos_temp.y;
	position_target.h = pos_temp.h;
	position_target.w = pos_temp.w;	m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);	m_frame.x += m_decalage.x;	m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);	m_frame.y += m_decalage.y;	if (m_frame.x < 0)		m_frame.x = 0;	if (m_frame.y < 0)		m_frame.y = 0;	if ((uint32_t) (m_frame.x + m_frame.w) > gStatic->static_data_weight())		m_frame.x = gStatic->static_data_weight() - m_frame.w;	if ((uint32_t) (m_frame.y + m_frame.h) > gStatic->static_data_height())		m_frame.y = gStatic->static_data_height() - m_frame.h;}
void Camera::display_background(Surface *background){	Rect pos;	pos.x = - m_frame.x  * BACKGROUND_SPEED;	pos.y = - m_frame.y * BACKGROUND_SPEED;	display_picture(background, &pos, true);}void Camera::display(Displayable * const entity) const{	Surface *picture = entity->current_picture();	if (picture != NULL) {		Rect pos = entity->position();		display_picture(picture, &pos);	}}
void Camera::display_events(Events_manager * const event_manager) const{	event_manager->display_events(this);}
void Camera::display_event(Event *event) const{	Surface *picture = event->current_picture();	if (picture != NULL) {
		Rect pos_event = event->current_pos();		display_picture(picture, &pos_event);	}}Rect Camera::frame() const{
    Rect pos_temp;
    pos_temp.x = m_frame.x;
    pos_temp.y = m_frame.y;
    pos_temp.h = m_frame.h;
    pos_temp.w = m_frame.w;	return pos_temp;}void Camera::display_picture(Surface *surf, Rect *pos, bool fixe) const{
    if ( fixe ) {
        SDL_Rect * pos_sdl = new SDL_Rect;
        pos_sdl->x = (int)pos->x;
        pos_sdl->y = (int)pos->y;
        pos_sdl->h = (unsigned int)pos->h;
        pos_sdl->w = (unsigned int)pos->w;        SDL_BlitSurface(surf->get_surface(), NULL, m_screen, pos_sdl);        delete pos_sdl;
    } else {
        Rect curr = *pos;
        curr.x -= m_frame.x;
		curr.y -= m_frame.y;
		display_picture(surf, &curr, true);
    }}
void Camera::display_picture(SDL_Surface *surf, Rect *pos){
    SDL_Rect * pos_sdl = new SDL_Rect;
    pos_sdl->x = (int)pos->x;
    pos_sdl->y = (int)pos->y;
    pos_sdl->h = (unsigned int)pos->h;
    pos_sdl->w = (unsigned int)pos->w;	SDL_BlitSurface(surf, NULL, m_screen, pos_sdl);	delete pos_sdl;}
void Camera::flip_camera(){	SDL_Flip(m_screen);}#ifdef DEBUG_COLLvoid Camera::display_green_coll(Rect pos) {	display_picture(m_green_coll, &pos);}void Camera::display_red_coll(Rect pos) {	display_picture(m_red_coll, &pos);}#endif