/**
 * 	@file triggerable.cpp
 * 	@brief implémentation de la classe Triggerables
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <stdint.h>

#include "Triggerable.h"
#include "util/debug.h"
#include "util/globals.h"
#include "util/Analyser.h"
#include "util/repertories.h"
#include "actors/Babar.h"
#include "actors/MonstersManager.h"
#include "video/Talks.h"
#include "video/GraphicEngine.h"


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
	if (m_nature == "monster") {
		process_monster();
	} else if (m_nature == "dialog") {
		process_dialog();
	} else if (m_nature == "alert") {
		process_alert();
	} else {
		PRINT_DEBUG(1, "Erreur: trigger non reconnu");
	}
}

void Triggerable::process_monster()
{
	gGameEngine->get_monsters_manager()->load_monster(m_text, m_x, m_y);
}

void Triggerable::process_dialog()
{
	gGraphics->get_talks()->display_text(m_text);
}

void Triggerable::process_alert()
{
	gGraphics->alert(m_text);
}
