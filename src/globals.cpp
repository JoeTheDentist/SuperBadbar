
#include <string>
#include <SDL/SDL.h>
#include <stdint.h>

#include "keyboard.h"
#include "debug.h"
#include "static_data.h"
#include "lists.h"
#include "statics.h"
#include "sprites.h"
#include "globals.h"
#include "game.h"
#include "talks.h"     
#include "dynamic_data.h"


SDL_Surface *screen;
uint32_t window_height = 600;
uint32_t window_weight = 800;
Talks talks;
bool full_screen = false;
