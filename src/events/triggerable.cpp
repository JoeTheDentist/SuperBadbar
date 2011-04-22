/**
 * 	@file triggerable.cpp
 * 	@brief implémentation de la classe Triggerables
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <stdint.h>

#include "triggerable.h"
#include "../util/debug.h"
#include "../util/globals.h"
#include "../util/analyser.h"
#include "../util/repertories.h"
#include "../actors/babar.h"
#include "../actors/monsters_manager.h"
#include "../video/talks.h"


Triggerable::Triggerable(Analyser &analyser)
{
	PRINT_CONSTR(3, "Construction d'un triggerable");
	std::string keywork;
	while (true) {
		keywork = analyser.read_between_char('#');
		if (keywork == "nature")
			m_nature = analyser.read_string();
		else if (keywork == "x")
			m_x = analyser.read_int();
		else if (keywork == "y") 
			m_y = analyser.read_int();
		else if (keywork == "text") 
			m_text = analyser.read_between_char('"');
		else if (keywork == "endtriggerable")
			break;
		else {
			PRINT_DEBUG(1, "ERREUR DANS LECTURE DE TRIGGERABLE");
			break;
		}
	}
}

Triggerable::~Triggerable()
{
}

void Triggerable::start()
{
	PRINT_DEBUG(1,"START TRIGGERABLE");
	if (m_nature == "monster") {
		PRINT_DEBUG(1, "A FAIRE: APPARITION D'UN MONSTRE %s en %d %d", m_text.c_str(), m_x, m_y);
		process_monster();
	} else {
		PRINT_DEBUG(1, "Erreur: trigger non reconnu");
	}
}

void Triggerable::process_monster()
{
	gGame_engine->get_monsters_manager()->load_monster(m_text, m_x, m_y);	
}
