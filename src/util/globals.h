
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

class Sound_engine;
class Collisions_manager;
class Static_data;
class Projectiles_manager;
class Events_manager;
class Babar;
class Sprites_manager;
class Animated_set_manager;
class Graphic_engine;
class Keyboard;
class Stats;
class Players_manager;

#include <sstream>

#include "../util/repertories.h"
#include "../actors/actor.h"
#include "../sound/sound_engine.h"
#include "../physic/collisions_manager.h"
#include "../game/static_data.h"
#include "../video/graphic_engine.h"
#include "../game/game_engine.h"
#include "../sets/animated_set_manager.h"
#include "../players/players_manager.h"

#define BOX_SIZE 5

#define NO_COLL 0x0
#define FULL_COLL 0xF
#define DOWN_COLL 0x4

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BACKGROUND_SPEED 0.5 /* vitesse de déplacement du fond d'écran par rapport à Babar */
#ifdef WIN32
    #define RAC ".."
#else
    #define RAC ".."
#endif

extern Sound_engine * gSound;
extern Collisions_manager * gCollision;
extern Static_data * gStatic;
extern Projectiles_manager * gProj;
extern Events_manager * gEvent;
//extern Babar * gBabar; /* liste si multi */
extern Graphic_engine * gGraphics;
extern Game_engine * gGame_engine;
extern Keyboard * gKeyboard;
extern Stats * gStats; /* liste si multi */
extern Players_manager * gPlayers;

extern int * gLocal_id;

double dist(Rect A, Rect B);

/**
 * Fonction permettant de savoir si un fichier existe ou non.
 * /!\ Il ne prend pas en compte la case. /!\
 * Avantage, ne depend pas du fait qu'on ait des permissions ou non sur le fichier.
 *
 * Code de DPAK, http://www.techbytes.ca/techbyte103.html.
 */
bool FileExists(std::string strFilename);

template <class T>
inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif
