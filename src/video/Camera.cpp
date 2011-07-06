/**
#include "../../lib/SDL/include/SDL/SDL_opengl.h"
    PRINT_CONSTR(1, "Construction de la camera")
	m_frame.x = 0;
	if (target) {
	m_frame.w = WINDOW_WIDTH;
    Rect pos_temp = target->position();
	SDL_Rect position_target;
	position_target.x = pos_temp.x;
	m_target = target;
	if (m_target->direction_v() != 0) {
	if(m_target->direction_v() == 0) {
	Rect pos_temp = m_target->position();
	position_target.x = pos_temp.x;
	position_target.y = pos_temp.y;
	position_target.h = pos_temp.h;
	position_target.w = pos_temp.w;
void Camera::display_background(Surface *background)

void Camera::display_event(Event *event) const
		Rect pos_event = event->current_pos();
    Rect pos_temp;
    pos_temp.x = m_frame.x;
    pos_temp.y = m_frame.y;
    pos_temp.h = m_frame.h;
    pos_temp.w = m_frame.w;
    if ( surf ) {
        if ( fixe ) {
            SDL_Rect pos_sdl;
            pos_sdl.x = (int)pos->x;
            pos_sdl.y = (int)pos->y;
            pos_sdl.h = (unsigned int)pos->h;
            pos_sdl.w = (unsigned int)pos->w;
            Rect curr = *pos;
            curr.x -= m_frame.x;
            curr.y -= m_frame.y;
            display_picture(surf, &curr, true);
        }
    }

    SDL_Rect * pos_sdl = new SDL_Rect;
    pos_sdl->x = (int)pos->x;
    pos_sdl->y = (int)pos->y;
    pos_sdl->h = (unsigned int)pos->h;
    pos_sdl->w = (unsigned int)pos->w;
