/**
 * 	@file graphic_engine.cpp
 * 	@brief Implémentation de la classe Graphic_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 
#include "graphic_engine.h"
#include "../sprites/babar.h"
#include "../video/camera.h"
#include "../game/static_data.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>


Graphic_engine::Graphic_engine(): m_camera(new Camera())
{
	PRINT_TRACE(1, "Initialisation de SDL")
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de la SDL")
		return;
	}
	PRINT_TRACE(1, "Initialisation de TTF")
	if (TTF_Init() == -1) {
		PRINT_DEBUG(1, "Erreur d'initialisation de TTF");
		return;
	}
}

Graphic_engine::~Graphic_engine()
{
	delete m_camera;
	TTF_Quit();
	SDL_Quit();
}

void Graphic_engine::init_graphic_engine(Babar *babar)
{
	m_camera->init_camera(babar);
}

Camera *Graphic_engine::get_camera()
{
	return m_camera;
}

void Graphic_engine::update(Static_data *static_data)
{
	m_camera->update_pos(static_data);
}
