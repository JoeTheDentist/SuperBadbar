
/**
 * 	@file globals.h
 * 	@brief Constantes /types utilisés par plusieurs classes
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _GLOBALS_
#define _GLOBALS_

#include "../util/repertories.h"
#include "../sound/sound_engine.h"
#include "../game/collisions_manager.h"
#include "../game/static_data.h"

#define BOX_SIZE 5

#define NO_COLL 0x0
#define FULL_COLL 0xF
#define DOWN_COLL 0x4

#define WINDOW_WEIGHT 800
#define WINDOW_HEIGHT 600

#define BACKGROUND_SPEED 0.5 /* vitesse de déplacement du fond d'écran par rapport à Babar */
#ifdef WIN32
    #define RAC ".."
#else
    #define RAC ".."
#endif

class Sound_engine;
class Collisions_manager;
class Static_data;
class Projectiles_manager;
class Events_manager;
class Babar;
class Animation_engine;

extern Sound_engine * gSound;
extern Collisions_manager * gCollision;
extern Static_data * gStatic;
extern Projectiles_manager * gProj;
extern Events_manager * gEvent;
extern Babar * gBabar;
extern Animation_engine * gAnims;

double dist(Rect A, Rect B);

#endif
