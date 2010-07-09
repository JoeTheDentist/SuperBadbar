
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "lists.h"
#include "sprites.h"


Monstre_list::Monstre_list()
{
	m_list = NULL;
}

Monstre_list::~Monstre_list()
{
	while (m_list != NULL){
		m_list->monstre.~Monstre();
		m_list = m_list->suiv;
	}
}

void Monstre_list::ajouter_monstre(uint32_t type, SDL_Rect pos, uint32_t area)
{
	struct cellule_monstre *L = NULL;
	Monstre monstre(type, pos, area);
	L = new struct cellule_monstre;
	L->monstre = monstre;
	L->suiv = m_list;
	m_list = L;
}
