/**
 * 	@file BindablePlatform.cpp
 * 	@brief Implementation de la classe BindablePlatform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <math.h>
#include "BindablePlatform.h"
#include "game/StaticData.h"
#include "video/Camera.h"
#include "video/Surface.h"
#include "actors/Babar.h"
#include "util/Analyser.h"
#include "physic/CollisionsManager.h"
#include "physic/CollisionsMatrix.h"
#include "video/Displayable.h"
#include "players/PlayersManager.h"

BindablePlatform::BindablePlatform()
{
    m_can_bind = 1;
    m_babar = NULL;
}

BindablePlatform::~BindablePlatform()
{
    if (m_babar)
    {
        m_babar->unbind();
    }
}

void BindablePlatform::init_bindable_platform (int posx, int posy, std::string file_name)
{
    m_pos.x = posx;
    m_pos.y = posy;

    file_name = PIC_STATICS_R + file_name;
    m_image = new Surface (file_name + ".png");
    m_pos.h = m_image->h();
    m_pos.w = m_image->w();
    Analyser analyser;
    analyser.open (file_name + ".col");
    m_collisions_matrix_w = analyser.read_int();
    m_collisions_matrix_h = analyser.read_int();
    m_collisions_matrix = new unsigned int*[m_collisions_matrix_w];
    for (int i = 0; i < m_collisions_matrix_w; i++)
    {
        m_collisions_matrix[i] = new unsigned int[m_collisions_matrix_h];
    }
    for (int j = 0; j < m_collisions_matrix_h; j++)
    {
        for (int i = 0; i < m_collisions_matrix_w; i++)
        {
            m_collisions_matrix[i][j] = analyser.read_int();
        }
    }
    analyser.close();
}

void BindablePlatform::update_pos()
{
    if (m_can_bind <= 0)
        m_can_bind++;
    m_phase++;
    /* descend */
    for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE)
    {
        if (check_babar() )
            gPlayers->local_player()->bind (this);
        m_pos.y += BOX_SIZE;
        if (m_babar)
            m_babar->check_unbind();
    }
    /* cas monte */
    for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE)
    {
        check_babar();
        m_pos.y -= BOX_SIZE;
        if (m_babar)
            m_babar->check_unbind();
    }
    /* droite */
    for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE)
    {
        check_babar();
        m_pos.x += 	BOX_SIZE;
        if (m_babar)
            m_babar->check_unbind();
    }
    /* gauche */
    for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE)
    {
        check_babar();
        m_pos.x -= BOX_SIZE;
        if (m_babar)
            m_babar->check_unbind();
    }
}

void BindablePlatform::update_speed()
{
}

void BindablePlatform::bind()
{
    m_babar = gPlayers->local_player();
}

void BindablePlatform::unbind()
{
    m_babar = NULL;
    m_can_bind = -3;
}

Rect BindablePlatform::speed() const
{
    return m_speed;
}

bool BindablePlatform::is_going_down()
{
    return m_speed.y > 0;
}

bool BindablePlatform::check_babar()
{
    if (m_can_bind <= 0)
        return false;
    if (m_babar != NULL)
        return false;
//~ 	if (gBabar->binded())
//~ 		return false;

    Rect babar_speed = gPlayers->local_player()->speed();
    Rect babar_pos = gPlayers->local_player()->position();
    if (babar_speed.y < m_speed.y)
        return false;
    Rect babar_rel_pos = gPlayers->local_player()->position();
    babar_pos.x -= m_pos.x;
    babar_pos.y -= m_pos.y;
    return CollisionsManager::is_down_coll (this->down_collision_type (babar_pos) );
}

bool BindablePlatform::dead()
{
    return m_pos.y < 0 || m_pos.y >  (int) gStatic->StaticData_height();
}

bool BindablePlatform::can_bind()
{
    return m_can_bind > 0;
}

#ifdef DEBUG_COLL
void BindablePlatform::display_coll (Camera *camera)
{

}
#endif
