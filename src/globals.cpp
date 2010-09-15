
#include <string>
#include <SDL/SDL.h>
#include <stdint.h>

#include "events.h"
#include "debug.h"
#include "levels.h"
#include "lists.h"
#include "statics.h"
#include "sprites.h"
#include "globals.h"
#include "game.h"
#include "talks.h"     
#include "dynamic_data.h"


SDL_Surface *screen;
List<Static*> statics;
Events_status Events_stat;
uint32_t window_height = 600;
uint32_t window_weight = 800;
uint32_t bottom = 2100;
Game game;
Talks talks;
bool full_screen = false;
//~ Dynamic_data dynamic_data;
