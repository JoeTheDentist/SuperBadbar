/**
 * 	@file CollisionsManager.h
 * 	@brief Implémentation de la classe CollisionsManager
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "CollisionsManager.h"
#include "stdint.h"
#include "util/Analyser.h"
#include "util/debug.h"
#include "util/repertories.h"
#include "actors/Babar.h"
#include "util/globals.h"
#include "video/Camera.h"
#include "physic/MovingPlatform.h"
#include "physic/FallingPlatform.h"
#include "physic/ChainedPlatform.h"
#include "players/PlayersManager.h"

#include <iostream>
#include <algorithm>

CollisionsManager::CollisionsManager()
{
    PRINT_CONSTR (1, "Construction de CollisionsManager")
}

CollisionsManager::~CollisionsManager()
{
    for (std::list<BindablePlatform *>::const_iterator it = m_moving_platforms.begin();
            it != m_moving_platforms.end(); it++)
    {
        delete (*it);
    }
    for (std::list<std::pair<BindablePlatform *, int> > ::const_iterator it = m_waiting_platforms.begin();
            it != m_waiting_platforms.end(); it++)
    {
        delete (*it).first;
    }
    delete m_matrix;
}

void CollisionsManager::init_collisions_manager (int level)
{
    Analyser analyser;
    std::string str_lvl;
    char str[3];
    sprintf (str, "%d", level);
    str_lvl = str;
    init_collisions_manager (LEVELS_R + "level" + str_lvl + ".lvl");
}

void CollisionsManager::init_collisions_manager (std::string level_name)
{
    Analyser analyser;
    analyser.open (level_name);
    analyser.find_string ("#Level_dimensions#");
    int w = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
    int h = analyser.read_int() / BACKGROUND_SPEED / BOX_SIZE;
    m_matrix = new CollisionsMatrix (w, h);
    init_statics (analyser);
    init_moving_plateforms (analyser);
    analyser.close();
}

void CollisionsManager::init_statics (Analyser &analyser)
{
    // ATTENTION: ici on charge les collisions des statics, mais pas leurs images
    analyser.find_string ("#Statics#");
    analyser.read_int();
    std::string static_name = analyser.read_string();
    while (static_name[0] != '!')
    {
        int x = analyser.read_int();
        int y = analyser.read_int();
        int variableCol = analyser.read_int();
        analyser.read_int();
        m_matrix->addStatic (x, y, variableCol, static_name);
        static_name = analyser.read_string();
    }
}

void CollisionsManager::init_moving_plateforms (Analyser &analyser)
{
    if (analyser.find_string ("#MovingPlatforms#") )
    {
        int platforms_number = analyser.read_int();
        for (int i = 0; i  < platforms_number; i++)
        {
            addPlatform (new MovingPlatform (analyser) );
        }
    }
    if (analyser.find_string ("#FallingPlatforms#") )
    {
        int platforms_number = analyser.read_int();
        for (int i = 0; i  < platforms_number; i++)
        {
            addPlatform (new FallingPlatform (analyser, this) );
        }
    }
//~ 	addPlatform(new ChainedPlatform(analyser));
}

void CollisionsManager::addPlatform (BindablePlatform *platform, int wait)
{
    if (wait == 0)
        m_moving_platforms.push_back (platform);
    else
        m_waiting_platforms.push_back (std::pair<BindablePlatform *, int> (platform, wait) );
}

bool CollisionsManager::check_collision (Rect A, Rect B)
{
    uint16_t A_right = A.x + A.w;
    uint16_t B_right = B.x + B.w;
    uint16_t A_bottom = A.y + A.h;
    uint16_t B_bottom = B.y + B.h;
    bool A_in_B = ( (B.x < A.x && A.x < B_right) || (B.x < A_right && A_right < B_right ) ) && ( (B.y < A.y && A.y < B_bottom) || (B.y < A_bottom && A_bottom < B_bottom ) );
    bool B_in_A = ( (A.x < B.x && B.x < A_right) || (A.x < B_right && B_right < A_right ) ) && ( (A.y < B.y && B.y < A_bottom) || (A.y < B_bottom && B_bottom < A_bottom ) );
    return A_in_B || B_in_A;
}

void CollisionsManager::display_platforms (Camera * const camera) const
{
    for (std::list<BindablePlatform *>::const_iterator it = m_moving_platforms.begin();
            it != m_moving_platforms.end(); it++)
    {
        camera->display ( (*it) );
#ifdef DEBUG_COLL
        (*it)->display_coll (camera);
#endif
    }


}

void CollisionsManager::update_platforms_pos()
{
    for (std::list<BindablePlatform *>::const_iterator it = m_moving_platforms.begin();
            it != m_moving_platforms.end(); it++)
    {
        (*it)->update_pos();
    }
}

void CollisionsManager::update_platforms_speed()
{
    for (std::list<BindablePlatform *>::const_iterator it = m_moving_platforms.begin();
            it != m_moving_platforms.end(); it++)
    {
        (*it)->update_speed();
    }
}

void CollisionsManager::update_babar_platforms()
{
    for (std::list<BindablePlatform *>::const_iterator it = m_moving_platforms.begin();
            it != m_moving_platforms.end(); it++)
    {
        if ( (*it)->check_babar() )
        {
            (*it)->bind();
            gPlayers->local_player()->bind ( (*it) );
        }
    }
}

void CollisionsManager::update_dead_platforms()
{
    for (std::list<BindablePlatform *>::iterator it = m_moving_platforms.begin();
            it != m_moving_platforms.end();)
    {
        if ( (*it)->dead() )
        {
            delete (*it);
            it = m_moving_platforms.erase (it);
        }
        else
        {
            it++;
        }
    }
}

void CollisionsManager::update_waiting_list()
{
    std::list<std::pair<BindablePlatform *, int> >::iterator it;
    for (it = m_waiting_platforms.begin(); it != m_waiting_platforms.end(); )
    {
        (*it).second--;
        if ( (*it).second <= 0)
        {
            addPlatform ( (*it).first);
            it = m_waiting_platforms.erase (it);
        }
        else
        {
            it++;
        }
    }
}


bool CollisionsManager::is_up_coll (uint32_t coll_number)
{
    return ( (coll_number & 0x8) == 0x8);
}

bool CollisionsManager::is_down_coll (uint32_t coll_number)
{
    return ( (coll_number & 0x4) == 0x4);
}

bool CollisionsManager::is_left_coll (uint32_t coll_number)
{
    return ( (coll_number & 0x2) == 0x2);
}

bool CollisionsManager::is_right_coll (uint32_t coll_number)
{
    if ( ( (coll_number & 0x1) == 0x1) )
    {
        PRINT_DEBUG (1, "RIGHT COOOOOOOOL");
//~ 		Surface *pic = new Surface("plop");
//~ 		int plop = pic->w();
//~ 		int yop = plop;
//~ 		return plop;
    }
    return ( (coll_number & 0x1) == 0x1);
}

#ifdef DEBUG_COLL
void CollisionsManager::display_coll (Camera *camera)
{
    m_matrix->display_coll (camera);
}
#endif

