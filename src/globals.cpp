
#include <string>
#include <SDL/SDL.h>
#include <stdint.h>

#include "events.h"
#include "levels.h"
#include "lists.h"
#include "statics.h"
#include "globals.h"


SDL_Surface *screen;
List<Static*> statics;
Events_status Events_stat;
uint32_t window_height = 600;
uint32_t window_weight = 800;
uint32_t bottom = level_height+50;
uint32_t level_height = 4000;
uint32_t level_weight = 4000;
Level curr_lvl;
