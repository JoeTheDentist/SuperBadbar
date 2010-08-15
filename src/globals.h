/**
 * Contient les variables globales du projet
**/

#ifndef _GLOBALS_
#define _GLOBALS_

#include <string>
#include <SDL/SDL.h>
#include "statics.h"
#include "events.h"
#include "levels.h"
#include "lists.h"
#include "sprites.h"

extern SDL_Surface *screen;		/* ecran de jeu */
extern List<Static*> statics;  /* liste des statics à afficher */
extern List<Projectile*> projectiles;  /* liste des projectiles à l'écran */
extern Events_status Events_stat; 	/* tables des touches enfoncées */
extern uint32_t window_height;		/* hauteur de la fenêtre de jeu */
extern uint32_t window_weight;		/* largeur de la fenêtre de jeu */
extern uint32_t bottom;             /* Sol, babar ne peut pas aller plus bas, temporaraire, faire avec les static ensuite */
extern Level curr_lvl;           /* Niveau en cours */

#endif
