/**
 * 	@file graphic_engine.cpp
 * 	@brief Implémentation de la classe Graphic_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>


int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {;
	}

	SDL_Quit();	
	return 0;
}