#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "collision_matrix.h"


int main(int argc, char *argv[])
{
	Collision_matrix grille("test.col");
	grille.save("copie.col");

	return 0;
}
