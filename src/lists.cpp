
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "lists.h"
#include "sprites.h"


Monster_list::Monster_list()
{
	m_list = NULL;
}

Monster_list::~Monster_list()
{
	while (m_list != NULL){
		m_list->monster.~Monster();
		m_list = m_list->suiv;
	}
}

void Monster_list::add_monster(uint32_t type, SDL_Rect pos, uint32_t area)
{
	struct cellule_monster *L = NULL;
	Monster monster(type, pos, area);
	L = new struct cellule_monster;
	L->monster = monster;
	L->suiv = m_list;
	m_list = L;
}
