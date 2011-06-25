
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

class SoundEngine;
class CollisionsManager;
class StaticData;
class ProjectilesManager;
class EventsManager;
class Babar;
class SpritesManager;
class AnimatedSetManager;
class GraphicEngine;
class Keyboard;
class Stats;
class PlayersManager;

#include <sstream>

#include "../util/repertories.h"
#include "../actors/actor.h"
#include "../sound/SoundEngine.h"
#include "../physic/CollisionsManager.h"
#include "../game/StaticData.h"
#include "../video/GraphicEngine.h"
#include "../game/GameEngine.h"
#include "../sets/AnimatedSetManager.h"
#include "../players/PlayersManager.h"

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

extern SoundEngine * gSound;
extern CollisionsManager * gCollision;
extern StaticData * gStatic;
extern ProjectilesManager * gProj;
extern EventsManager * gEvent;
//extern Babar * gBabar; /* liste si multi */
extern GraphicEngine * gGraphics;
extern GameEngine * gGameEngine;
extern Keyboard * gKeyboard;
extern Stats * gStats; /* liste si multi */
extern PlayersManager * gPlayers;

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
