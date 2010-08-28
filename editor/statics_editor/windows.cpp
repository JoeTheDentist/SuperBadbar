
#include <iostream>
#include <stdint.h>
#include <string>

#include "windows.h"
#include "editor.h"

Window::Window(std::string static_name)
{
	m_background = SDL_LoadBMP((STATICS_DIR + static_name + PICS_EXT).c_str());
	if (m_background == NULL) {
		std::cout << "Erreur: impossible de trouver le fichier " << STATICS_DIR + static_name + PICS_EXT << std::endl;
		return;
	}
	/* chargement de la fenetre */
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL");
	}
	m_screen = SDL_SetVideoMode(m_background->w, m_background->h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Editeur de statics de superbabar", NULL);
	SDL_BlitSurface(m_background, NULL, m_screen, NULL);
	/* chargement des images de collision: vert pour downcollision et rouge pour un block de collision */
	m_square_block = SDL_CreateRGBSurface(SDL_SWSURFACE, SQUARE_SIZE, SQUARE_SIZE, 32, 0, 0,  0, 0);
	SDL_FillRect(m_square_block, NULL,  SDL_MapRGB(m_screen->format, 255, 0, 0));	
	m_square_down_coll = SDL_CreateRGBSurface(SDL_SWSURFACE, SQUARE_SIZE, SQUARE_SIZE, 32, 0, 0,  0, 0);
	SDL_FillRect(m_square_down_coll, NULL,  SDL_MapRGB(m_screen->format, 0, 255, 0));
	/* flip */
	SDL_Flip(m_screen);
}

Window::~Window()
{
	SDL_FreeSurface(m_square_down_coll);
	SDL_FreeSurface(m_square_block);
	SDL_FreeSurface(m_background);
	SDL_FreeSurface(m_screen);
}


void Window::blit_background()
{
	SDL_BlitSurface(m_background, NULL, m_screen, NULL);

}


void Window::blit_square(uint32_t weight, uint32_t height, uint32_t coll_type)
{
	SDL_Rect pos = {weight - (weight % SQUARE_SIZE), height - (height % SQUARE_SIZE), 0, 0};
	SDL_Rect pos2;
	SDL_Surface *square;
	switch(coll_type) {
	case NO_COLL:
		square = SDL_CreateRGBSurface(SDL_SWSURFACE, SQUARE_SIZE, SQUARE_SIZE, 32, 0, 0,  0, 0);
		pos2.x = -weight;
		pos2.y = -height;
		SDL_BlitSurface(m_background, NULL, square, &pos2);                              
		SDL_BlitSurface(square, NULL, m_screen, &pos);
	break;
	case DOWN_COLL:
		SDL_BlitSurface(m_square_down_coll, NULL, m_screen, &pos);
		break;
	case FULL_COLL:
		SDL_BlitSurface(m_square_block, NULL, m_screen, &pos);
		break;
	default:
		break;
	}

}


void Window::flip_screen()
{
	SDL_Flip(m_screen);
}

uint32_t static_weight(std::string static_name)
{
	SDL_Surface *pic =SDL_LoadBMP((STATICS_DIR + static_name + PICS_EXT).c_str());
	if (pic == NULL) 
		return 0;
	SDL_FreeSurface(pic);
	return (pic->w / SQUARE_SIZE) + 1;
}

uint32_t static_height(std::string static_name)
{
	SDL_Surface *pic =SDL_LoadBMP((STATICS_DIR + static_name + PICS_EXT).c_str());
	if (pic == NULL) 
		return 0;
	SDL_FreeSurface(pic);
	return (pic->h / SQUARE_SIZE) + 1;
}
