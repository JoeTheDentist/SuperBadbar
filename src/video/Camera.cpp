/**
 * 	@file camera.cpp
 * 	@brief Impl√©mentation de la classe Camera
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#include "Camera.h"
#include "actors/Actor.h"
#include "actors/Babar.h"
#include "actors/Monster.h"
#include "actors/Projectile.h"
#include "events/EventsManager.h"
#include <events/Event.h>
#include "game/StaticData.h"
#include "physic/CollisionsManager.h"
#include <physic/MovingPlatform.h>
#include "util/globals.h"
#include "util/utils.h"
#include <video/Displayable.h>
#include <video/Statics.h>
#include "video/Surface.h"
#include <video/SurfaceCompositeItem.h>
//todo enlever:
#include <control/EventKeyboard.h>


Camera::Camera()
{
	PRINT_DEBUG(1, "Construction de la camera");
    m_target = NULL;
    m_screen = NULL;
	m_window = NULL;
	m_initialized = false;
}

Camera::~Camera()
{
    PRINT_CONSTR(1, "Destruction de la camera");
    PRINT_TRACE(1, "Fermeture de la fenetre");
	delete m_window;
}

void Camera::init_camera(Actor *target)
{
    m_frame.x = 0;
    m_frame.y = 0;
    if (target) {
        set_target(target);
    }
    m_frame.w = Constants::WINDOW_WIDTH;
    m_frame.h = Constants::WINDOW_HEIGHT;
    PRINT_TRACE(1, "Ouverture de la fenetre (de taille %d*%d)", m_frame.w, m_frame.h)
	if (!m_initialized) {
		if (Constants::FULL_SCREEN == 0) {
			m_window = new sf::RenderWindow(sf::VideoMode(m_frame.w, m_frame.h, 32), "SuperBadbar");
		} else {
			m_window = new sf::RenderWindow(sf::VideoMode(m_frame.w, m_frame.h, 32), "SuperBadbar", sf::Style::Fullscreen);
		}
		EventKeyboard::initEventKeyboard();
	}
	m_target = target;
#ifdef DEBUG_COLL
    m_green_coll = new Surface(PIC_DEBUG_R + "green_col.png");
    m_red_coll = new Surface(PIC_DEBUG_R + "red_col.png");
#endif
	m_initialized = true;
}

void Camera::set_target(Actor *target)
{
    Rect pos_temp = target->position();
	Rect position_target;
    position_target.x = pos_temp.x;
    position_target.y = pos_temp.y;
    position_target.h = pos_temp.h;
    position_target.w = pos_temp.w;
    m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);
    m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);
    m_target = target;
}

void Camera::update_decalage()
{
    //mise √  jour de la direction du decalage
    if (m_target->direction_h() != 0) {
        m_direction.x = m_target->direction_h();
    }

    // gestion du decalage direction
    m_decalage.x += m_direction.x* VITESSE_DECALAGE_CAMERA;
    if (m_decalage.x < -m_frame.w *MAX_DECALAGE_CAMERA)
        m_decalage.x = -m_frame.w * MAX_DECALAGE_CAMERA;
    if (m_decalage.x > m_frame.w * MAX_DECALAGE_CAMERA)
        m_decalage.x = m_frame.w * MAX_DECALAGE_CAMERA;

	m_decalage.x = 0;
}

void Camera::update_pos()
{
    update_decalage();
    Rect pos_temp = m_target->position();
	Rect position_target;
    position_target.x = pos_temp.x;
    position_target.y = pos_temp.y;
    position_target.h = pos_temp.h;
    position_target.w = pos_temp.w;
    m_frame.x = position_target.x + (position_target.w / 2) - (m_frame.w / 2);
    m_frame.x += m_decalage.x;
    m_frame.y = position_target.y + (position_target.h / 2) - (m_frame.h / 2);
    m_frame.y += m_decalage.y;
    if (m_frame.x < 0)
        m_frame.x = 0;
    if (m_frame.y < 0)
        m_frame.y = 0;
    if ((uint32_t) (m_frame.x + m_frame.w) > gStatic->StaticData_width())
        m_frame.x = gStatic->StaticData_width() - m_frame.w;
    if ((uint32_t) (m_frame.y + m_frame.h) > gStatic->StaticData_height())
        m_frame.y = gStatic->StaticData_height() - m_frame.h;
}

void Camera::display_background(Surface *background)
{
    Rect pos;
    pos.x = - m_frame.x  * BACKGROUND_SPEED;
    pos.y = - m_frame.y * BACKGROUND_SPEED;
    display_picture(background, &pos, true);
}

void Camera::display(Displayable * const entity) const
{
    Surface *picture = entity->current_picture();
    if (picture != NULL) {
        Rect pos = entity->position();
        display_picture(picture, &pos);
    }
}

void Camera::display_events(EventsManager * const event_manager) const
{
    event_manager->display_events(this);
}

void Camera::display_event(Event *event) const
{
    Surface *picture = event->current_picture();
    if (picture != NULL) {
        Rect pos_event = event->current_pos();
        display_picture(picture, &pos_event);
    }
}

Rect Camera::frame() const
{
    Rect pos_temp;
    pos_temp.x = m_frame.x;
    pos_temp.y = m_frame.y;
    pos_temp.h = m_frame.h;
    pos_temp.w = m_frame.w;
    return pos_temp;
}

int Camera::width() const
{
    return frame().w;
}

int Camera::height() const
{
    return frame().h;
}

void Camera::display_picture(Surface *surf, Rect *pos, bool fixe) const
{
    if ( surf ) {
        if ( fixe ) {
			sf::Drawable *drawable = surf->getSurface();
			if (!surf->getSurface())
				return;
			drawable->SetX(pos->x);
			drawable->SetY(pos->y);
			m_window->Draw(*drawable);
            std::vector<SurfaceCompositeItem *> *children = surf->children();
            if (children) {
                for (std::vector<SurfaceCompositeItem *>::iterator it = children->begin();
                it != children->end(); ++it) {
                    Rect poschild = (*it)->getPosInCompositeSurface() + *pos;
                    display_picture((*it)->getSurface(), &poschild, fixe);
                }
            }
        } else {
            Rect curr = *pos;
            curr.x -= m_frame.x;
            curr.y -= m_frame.y;
            display_picture(surf, &curr, true);
        }
    }
}

void Camera::flip_camera()
{
	m_window->Display();
}

#ifdef DEBUG_COLL
void Camera::display_green_coll(Rect pos)
{
    display_picture(m_green_coll, &pos);
}

void Camera::display_red_coll(Rect pos)
{
    display_picture(m_red_coll, &pos);
}
#endif
