/**
 * 	@file GraphicEngine.cpp
 * 	@brief Implémentation de la classe GraphicEngine
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include "GraphicEngine.h"
#include "actors/Babar.h"
#include "game/StaticData.h"
#include "players/PlayersManager.h"
#include "sprites/SpritesManager.h"
#include "video/Camera.h"
#include "video/Dashboard.h"
#include "video/PicturesContainer.h"
#include "video/GridsContainer.h"
#include "video/Talks.h"
#include "video/Surface.h"


GraphicEngine::GraphicEngine()
{
    PRINT_CONSTR (1, "Construction de GraphicEngine");
    m_camera = new Camera();
    m_talks = new Talks();
    m_dashboard = new Dashboard();
    m_sprites = new SpritesManager;
}

GraphicEngine::~GraphicEngine()
{
    PRINT_CONSTR (1, "Destruction de GraphicEngine");
    delete m_camera;
    delete m_talks;
    delete m_dashboard;
    PicturesContainer::Destroy();
    GridsContainer::Destroy();
    delete m_sprites;
}

void GraphicEngine::init_graphic_engine (bool game)
{
    if (game)
    {
        m_camera->init_camera (gPlayers->local_player() );
    }
    else
    {
        m_camera->init_camera (NULL);
    }
    m_talks->init_talks (m_camera);
    m_dashboard->init_dashboard();
}

void GraphicEngine::update()
{
    m_camera->update_pos();
    m_dashboard->update();
    m_sprites->update();
    m_sprites->delete_dead_sprites();
}

void GraphicEngine::draw_dashboard (Camera *camera)
{
    m_dashboard->draw_dashboard (camera);
}

void GraphicEngine::display_sprites (Camera * cam)
{
    m_sprites->display_sprites (cam);
}

void GraphicEngine::alert (std::string text)
{
    m_dashboard->alert (text);
}

Camera *GraphicEngine::get_camera()
{
    return m_camera;
}

Talks *GraphicEngine::get_talks()
{
    return m_talks;
}

SpritesManager * GraphicEngine::get_sprites_manager()
{
    return m_sprites;
}

void GraphicEngine::clean()
{
    m_sprites->clear();
}

void GraphicEngine::flip_camera()
{
    m_camera->flip_camera();
}
