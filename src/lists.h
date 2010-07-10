#ifndef _LISTES_
#define _LISTES_

#include "sprites.h"

struct cellule_monster {
	Monster monster;
	struct cellule_monster* suiv;
};

class Monster_list {
private:
	struct cellule_monster *m_list;
public:
	Monster_list();
	~Monster_list();
	void add_monster(uint32_t type, SDL_Rect pos, uint32_t area);
	
	
};



#endif