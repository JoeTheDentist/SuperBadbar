
#include <string>
#include <SDL/SDL.h>
#include <stdint.h>

#include "globals.h"
#include "events.h"


SDL_Surface *screen;
Events_status Events_stat;
uint32_t window_height = 600;
uint32_t window_weight = 800;
uint32_t bottom = window_height - 50;
