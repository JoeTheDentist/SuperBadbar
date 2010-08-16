
#ifndef _WINDOW_
#define _WINDOW_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>         
#include <string>


class Window{
private:                                                               
	SDL_Surface *m_screen; 				/* fenetre de l'éditeurf*/
	SDL_Surface *m_background; 			/* surface de fond d'écran */
	SDL_Rect m_camera;					/* position de la camera */
	SDL_Surface *m_monstre;
	SDL_Rect m_pos_monstre;
public:
	Window();												/* Constructeur par défaut */
	Window(std::string file_name);							/* Constructeur avec en paramètre le nom de fichier du niveau*/
	~Window();												/* Destructeur */
	SDL_Surface *screen();									/* Accesseur: retourne la surface correspondant à la fenetre*/
	void translate(int x, int y);
	void update_background();								/* Blit (sans raffraichir l'écran) le fond d'écran au bon endroit */
	void refresh();											/* rafraichit l'écran (affiche les surfaces blittées) */
	void display_pic(SDL_Surface *surface, SDL_Rect pos);	/* Blit (sans raffraichir) l'image à la bonne position par rapport à la camera */
	
	
};







#endif