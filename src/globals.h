/**
 * Contient les variables globales du projet 
**/

#ifndef _GLOBALS_
#define _GLOBALS_

#include <string>
#include <SDL/SDL.h>
#include "events.h"


extern SDL_Surface *screen;		/* ecran de jeu */
extern Events_status Events_stat; 	/* tables des touches enfoncées */
extern uint32_t window_height;		/* hauteur de la fenêtre de jeu */
extern uint32_t window_weight;		/* largeur de la fenêtre de jeu */

#endif