#include "Constants.h"
#include "../util/Analyser.h"
#include "../util/repertories.h"
#include <iostream>

int Constants::FULL_SCREEN = 0;
std::string Constants::TEST_LEVEL = "test.lvl";

#define ACO(yop) {yop}
#define QUOTE_(yop) #yop
#define QUOTE(yop) QUOTE_(yop)
#define QUOTE_ACO(yop) QUOTE(ACO(yop))
#define IDENTITY(yop) yop
#define CONST_INIT_INT(yop) \
if (analyser.find_string(QUOTE_ACO(yop))) { \
	 Constants::IDENTITY(yop) = analyser.read_int(); \
}
	

void Constants::init()
{
	Analyser analyser;
	analyser.open(DATA_R + "config.cfg");
	
//~ 	if (analyser.find_string("{FULL_SCREEN}")) {
//~ 		Constants::FULL_SCREEN = analyser.read_int();
//~ 	}
	CONST_INIT_INT(FULL_SCREEN);
	analyser.close();
}
