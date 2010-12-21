/**
 * 	@file surface.cpp
 * 	@brief Implémentation de la classe Surface
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 
#include <iostream>
#include <SDL/SDL.h>
#include "surface.h"
#include "../video/pictures_container.h"
#include "../util/debug.h"

Pictures_container Surface::m_pictures_container;



Surface::Surface(std::string filename)
{
	PRINT_CONSTR(1, "CONSTRUCTION DE LA CLASSE SURFACE");

}

Surface::~Surface()
{
	PRINT_CONSTR(1, "DESTRUCTION DE LA CLASSE SURFACE");
}
