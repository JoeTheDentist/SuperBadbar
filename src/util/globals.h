/**
 * Contient les variables globales du projet
**/

#ifndef _GLOBALS_
#define _GLOBALS_

#include "../util/repertories.h"

#define WINDOW_WEIGHT 800
#define WINDOW_HEIGHT 600
#define BACKGROUND_SPEED 0.5 /* vitesse de déplacement du fond d'écran par rapport à Babar */
#ifdef WIN32
    #define RAC ".."
#else
    #define RAC ".."
#endif

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

#endif
