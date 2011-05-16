/**
 * 	@file graphic_engine.cpp
 * 	@brief Implémentation de la classe Graphic_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include "graphic_engine.h"
#include "../util/debug.h"
#include "../actors/babar.h"
#include "../video/camera.h"
#include "../video/talks.h"
#include "../video/dashboard.h"
#include "../video/pictures_container.h"
#include "../game/static_data.h"
#include "../video/surface.h"
#include "../sprites/sprites_manager.h"
#include "../players/players_manager.h"

Graphic_engine::Graphic_engine()
{
	PRINT_CONSTR(1, "Construction de Graphic_engine")
	PRINT_TRACE(1, "Initialisation de SDL")
	m_camera = new Camera();
	m_talks = new Talks();
	m_dashboard = new Dashboard();
	m_pictures_container = new Pictures_container();
	m_sprites = new Sprites_manager;
	Surface::set_pictures_container(m_pictures_container);
}

Graphic_engine::~Graphic_engine()
{
	PRINT_CONSTR(1, "Destruction de Graphic_engine")
	delete m_camera;
	delete m_talks;
	delete m_dashboard;
	delete m_pictures_container;
	delete m_sprites;
}

void Graphic_engine::init_graphic_engine(bool game)
{
	if (game) {
		m_camera->init_camera(gPlayers->local_player());
		m_talks->init_talks(m_camera, m_pictures_container);
		m_dashboard->init_dashboard(m_pictures_container);
	} else {
		m_camera->init_camera(NULL);
	}
}

void Graphic_engine::update()
{
	m_camera->update_pos();
	m_dashboard->update();
	m_sprites->update();
	m_sprites->delete_dead_sprites();
}

void Graphic_engine::draw_dashboard(Camera *camera)
{
	m_dashboard->draw_dashboard(camera);
}

void Graphic_engine::display_sprites(Camera * cam)
{
    m_sprites->display_sprites(cam);
}

void Graphic_engine::alert(std::string text)
{
    m_dashboard->alert(text);
}


Camera *Graphic_engine::get_camera()
{
	return m_camera;
}

Talks *Graphic_engine::get_talks()
{
	return m_talks;
}

Pictures_container *Graphic_engine::get_pictures_container()
{
	return m_pictures_container;
}

Sprites_manager * Graphic_engine::get_sprites_manager()
{
    return m_sprites;
}

void Graphic_engine::clean()
{
    m_sprites->clear();
}
