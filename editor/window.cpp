

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
	m_camera.x = 0;
	m_camera.y = 0;

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
	m_monstre = SDL_LoadBMP("blob.bmp");
	m_pos_monstre.x = 50;
	m_pos_monstre.y = 50;

	
	SDL_BlitSurface(m_background, NULL, m_screen, &m_camera);

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


void Window::translate(int x, int y)
{
	m_camera.x += x;
	m_camera.y += y;
}

void Window::update_background()
{
	SDL_Rect pos_background;
	pos_background.x = -m_camera.x;
	pos_background.y = -m_camera.y;

	SDL_BlitSurface(m_background, NULL, m_screen, &pos_background);
		display_pic(m_monstre, m_pos_monstre);

}

void Window::display_pic(SDL_Surface *surface, SDL_Rect pos)
{
	pos.x -= m_camera.x;
	pos.y -= m_camera.y;
	SDL_BlitSurface(surface, NULL, m_screen, &pos);
}

void Window::refresh()
{
	SDL_Flip(m_screen);
}