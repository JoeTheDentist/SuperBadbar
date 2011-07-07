#include "Constants.h"
#include "../util/Analyser.h"
#include "../util/repertories.h"
#include <iostream>
int Constants::FULL_SCREEN = 0;





void Constants::init()
{
	Analyser analyser;
	analyser.open(DATA_R + "config.cfg");
	
	if (analyser.find_string("#FULL_SCREEN#")) {
		Constants::FULL_SCREEN = analyser.read_int();
		std::cout << "FUUUUUUULL" << Constants::FULL_SCREEN << std::endl;
	}
	analyser.close();
}
