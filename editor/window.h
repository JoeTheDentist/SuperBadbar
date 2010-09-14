
#ifndef _WINDOW_
#define _WINDOW_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>         
#include <string>

#define CAMERA_W 600		
#define CAMERA_H 400
#define BACKGROUND_SPEED 0.5

class Window{
private:                                                               
	SDL_Surface *m_screen; 				/* fenetre de l'éditeur*/
	SDL_Surface *m_background; 		/* surface de fond d'écran */
	SDL_Rect m_camera;					/* position de la camera (les champs .w et .h sont aussi pertinents)*/
	size_t m_height;
	size_t m_weight;
	std::string m_background_name;

public:
	Window();												/* Constructeur par défaut */
	Window(std::string file_name);							/* Constructeur avec en paramètre le nom de fichier du niveau*/
	~Window();												/* Destructeur */
	void save(FILE* file);
	SDL_Surface *screen();									/* Accesseur: retourne la surface correspondant à la fenetre*/
	SDL_Rect camera();										/* Accesseur: retourne m_camera */
	void translate(int x, int y);
	void update_background();								/* Blit (sans raffraichir l'écran) le fond d'écran au bon endroit */
	void refresh();											/* rafraichit l'écran (affiche les surfaces blittées) */
	void display_pic(SDL_Surface *surface, SDL_Rect pos);	/* Blit (sans raffraichir) l'image à la bonne position par rapport à la camera */
	
	
};







#endif