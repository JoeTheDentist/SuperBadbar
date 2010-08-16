

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>         
#include <string>

#include "window.h"
#include "files.h"

Window::Window()
{
	
}


Window::Window(std::string file_name)
{
	FILE *file = NULL;
	size_t weight, height;
	char background[100];
	SDL_Rect background_pos = {0,0,0,0};
	

	/* recherche des informations dans le fichier file_name*/
	file = fopen(file_name.c_str(), "r");
	if (file == NULL)
		fprintf(stderr, "Erreur lors de l'ouverture du fichier %s", file_name.c_str());
	fseek(file, 0, SEEK_SET);
	fscanf(file, "%d", &weight);
	fscanf(file, "%d", &height);
	find_string("Background:", file);	
	fscanf(file, "%s", background);
	fclose(file);
	/* chargement de la fenetre */
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL");
	}
	m_screen = SDL_SetVideoMode(weight, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);
	SDL_WM_SetCaption("Editeur de superbabar", NULL);
    m_background = SDL_LoadBMP(background);   
	SDL_BlitSurface(m_background, NULL, m_screen, &background_pos);
	SDL_Flip(m_screen);
	
}


Window::~Window()
{
	SDL_FreeSurface(m_screen);
	SDL_Quit();
}

SDL_Surface *Window::screen()
{
	return m_screen;
}