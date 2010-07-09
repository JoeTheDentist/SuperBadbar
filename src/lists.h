#ifndef _LISTES_
#define _LISTES_

#include "sprites.h"

struct cellule_monstre {
	Monstre monstre;
	struct cellule_monstre* suiv;
};

class Monstre_list {
private:
	struct cellule_monstre *m_list;
public:
	Monstre_list();
	~Monstre_list();
	void ajouter_monstre(uint32_t type, SDL_Rect pos, uint32_t area);
	
	
};



#endif