#include <iostream>
#include <SDL/SDL.h>

#include "collisions.h"

bool check_collision(SDL_Rect A, SDL_Rect B) //Optimisable?
{
	uint16_t A_right = A.x + A.w;
	uint16_t B_right = B.x + B.w;
	uint16_t A_bottom = A.y + A.h;
	uint16_t B_bottom = B.y + B.h;
	bool A_in_B = ((B.x < A.x && A.x < B_right) || (B.x < A_right && A_right < B_right )) && ((B.y < A.y && A.y < B_bottom) || (B.y < A_bottom && A_bottom < B_bottom ));
	bool B_in_A = ((A.x < B.x && B.x < A_right) || (A.x < B_right && B_right < A_right )) && ((A.y < B.y && B.y < A_bottom) || (A.y < B_bottom && B_bottom < A_bottom ));
	return A_in_B || B_in_A;
}

bool is_up_coll(uint32_t coll_number)
{
	return ((coll_number & 0x8) == 0x8);
}

bool is_down_coll(uint32_t coll_number)
{
	return ((coll_number & 0x4) == 0x4);
}

bool is_left_coll(uint32_t coll_number)
{
	return ((coll_number & 0x2) == 0x2);
}

bool is_right_coll(uint32_t coll_number)
{
	return ((coll_number & 0x1) == 0x1);
}

bool is_climb_coll(uint32_t coll_number)
{
	return ((coll_number & 0x10) == 0x10);
}

