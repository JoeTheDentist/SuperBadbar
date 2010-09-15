/**
 * Contient les variables globales du projet
**/

#ifndef _GLOBALS_
#define _GLOBALS_

#define BACKGROUND_SPEED 0.5 /* vitesse de déplacement du fond d'écran par rapport à Babar */


#include <string>
#include <SDL/SDL.h>
#include "sprites.h"

#include "statics.h"
#include "events.h"
#include "lists.h"
#include "talks.h"
#include "dynamic_data.h"
#include "levels.h"

class Projectile;   /* Pour éviter les bugs */
class Game;
class Monster;
class Dynamic_data;

extern SDL_Surface *screen;			/* ecran de jeu */
extern List<Static*> statics; 		/* liste des statics à afficher */
extern Events_status Events_stat; 	/* tables des touches enfoncées */
extern uint32_t window_height;		/* hauteur de la fenêtre de jeu */
extern uint32_t window_weight;		/* largeur de la fenêtre de jeu */
extern uint32_t bottom;             /* Sol, babar ne peut pas aller plus bas, temporaraire, faire avec les static ensuite */
extern Game game;                   /* Jeu */
extern Talks talks;					/* Boite de dialogues */
extern bool full_screen;			/* activation du mode full_screen */
//~ extern Dynamic_data dynamic_data;

#endif
