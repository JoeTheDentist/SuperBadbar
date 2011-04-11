
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
#include "../physic/collisions_manager.h"
#include "../game/static_data.h"
#include "../video/graphic_engine.h"
#include "../game/game_engine.h"

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
class Graphic_engine;
class Keyboard;
class Stats;

extern Sound_engine * gSound;
extern Collisions_manager * gCollision;
extern Static_data * gStatic;
extern Projectiles_manager * gProj; /* liste si multi */
extern Events_manager * gEvent;
extern Babar * gBabar; /* liste si multi */
extern Animation_engine * gAnims;
extern Graphic_engine *gGraphics;
extern Game_engine *gGame_engine;
extern Keyboard *gKeyboard;
extern Stats * gStats; /* liste si multi */

double dist(Rect A, Rect B);

#endif
