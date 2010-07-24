
#include <iostream>
#include <stdint.h>

#include "levels.h"


Level::Level()
{
}

Level::Level(uint32_t lvl)
{
	m_level = lvl;
	
	/* 
		A COMPLETER:
		faire appel à un analyseur pour récupérer les images du niveau
	*/
}

Level::~Level()
{
	/*
		A COMPLETER:
		libérer le tableau des images des monstres
	*/
}