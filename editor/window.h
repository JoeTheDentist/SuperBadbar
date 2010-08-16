
#ifndef _WINDOW_
#define _WINDOW_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>         
#include <string>


class Window{
private:
	SDL_Surface *m_screen; 
	SDL_Surface *m_background; 
	//~ SDL_Rect m_camera;

public:
	Window();														/* Constructeur par défaut */
	Window(std::string file_name);							/* Constructeur avec en paramètre le nom de fichier du niveau*/
	~Window();														/* Destructeur */
	SDL_Surface *screen();										/* Accesseur: retourne la surface correspondant à la fenetre*/
	
	
};







#endif