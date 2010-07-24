/**


**/

#ifndef _LEVELS_
#define _LEVELS_

#include "SDL/SDL.h"


class Level {
private:
	uint32_t m_level;		/* Numero du niveau */
	SDL_Surface ** m_monster_pic;	/* tableau des images des monstres présents dans le niveau*/
	
public:
	Level();			/* Constructeur par défaut*/
	Level(uint32_t lvl);		/* Constructeur avec précision du numéro de niveau */
	~Level();			/* Destructeur */
};



#endif