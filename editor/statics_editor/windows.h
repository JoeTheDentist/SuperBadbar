#ifndef _WINDOWS_
#define _WINDOWS_

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


class Window {
private:
	SDL_Surface *m_screen;			/* ecran de l'éditeur */
	SDL_Surface *m_background;		/* fond de l'éditeur (image du static) */
	SDL_Surface *m_square_block;		/* surface d'un carré de collision pleine */
	SDL_Surface *m_square_down_coll;	/* surface d'un carré de collision inférieure */
	SDL_Surface *m_square_climb_coll; 	/* surface d'un carré de collision climb */
public:
	Window(std::string static_name);/* constructeur à partir du fichier correspondant au static_name */
	~Window();						/* destructeur */
	void blit_background();			/* blit le fond d'écran */
	void blit_square(uint32_t weight, uint32_t height, uint32_t coll_type); /* blit un carré de type coll_type
																			weight et height sont en PIXELS */
	void flip_screen();				/* flip l'écran */
};

uint32_t static_weight(std::string static_name);	/* retourne la largeur d'un static en carrés de collision. Le fichier image correspondant doit exister */
uint32_t static_height(std::string static_name);	/* retourne la hauteur d'un static en carrés de collision. Le fichier image correspondant doit exister */



#endif
