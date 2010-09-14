

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>         
#include <string>

#include "window.h"
#include "files.h"
#include "editor.h"

Window::Window()
{
	
}


Window::Window(std::string file_name)
{
	FILE *file = NULL;
	std::string file_n = LEVELS_DIR + file_name;
	char background[100];
	m_camera.x = 0;
	m_camera.y = 0;

	/* recherche des informations dans le fichier file_name*/
	file = fopen(file_n.c_str(), "r");
	if (file == NULL)
		fprintf(stderr, "Erreur lors de l'ouverture du fichier %s", file_name.c_str());
	find_string("#Background#", file);
	fscanf(file, "%s", background);
	m_background_name = background;
	fclose(file);
	/* chargement de la fenetre */
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL");
	}
	fprintf(stderr, "%s", background);
	m_background = SDL_LoadBMP(background);
	m_weight = m_background->w / BACKGROUND_SPEED;
	m_height = m_background->h / BACKGROUND_SPEED;
	m_camera.w =  CAMERA_W;
	m_camera.h =  CAMERA_H;
	m_screen = SDL_SetVideoMode(m_camera.w, m_camera.h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Editeur de superbabar", NULL);
	SDL_BlitSurface(m_background, NULL, m_screen, &m_camera);
	SDL_Flip(m_screen);
}


Window::~Window()
{
	SDL_FreeSurface(m_screen);
	SDL_Quit();
}

void Window::save(FILE* file)
{
	fprintf(file, "#Background#\n%s\n\n", m_background_name.c_str());
}


SDL_Surface *Window::screen()
{
	return m_screen;
}

SDL_Rect Window::camera()
{
	return m_camera;
}

void Window::translate(int x, int y)
{
	m_camera.x += x;
	m_camera.y += y;
	if (m_camera.x < 0)
		m_camera.x = 0;
	if (m_camera.y < 0)
		m_camera.y = 0;
	if (m_camera.x + m_camera.w  > m_weight)
		m_camera.x = m_weight- m_camera.w;	
	if (m_camera.y + m_camera.h  > m_height)
		m_camera.y = m_height - m_camera.h;
}

void Window::update_background()
{
	SDL_Rect pos_background;
	pos_background.x = -m_camera.x * BACKGROUND_SPEED;
	pos_background.y = -m_camera.y * BACKGROUND_SPEED;

	SDL_BlitSurface(m_background, NULL, m_screen, &pos_background);

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