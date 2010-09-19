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
#include "keyboard.h"
#include "lists.h"
#include "talks.h"
#include "dynamic_data.h"
#include "static_data.h"

class Projectile;   /* Pour éviter les bugs */
//~ class Game;
class Monster;
class Dynamic_data;

extern uint32_t window_height;		/* hauteur de la fenêtre de jeu */
extern uint32_t window_weight;		/* largeur de la fenêtre de jeu */
extern bool full_screen;			/* activation du mode full_screen */

#endif
