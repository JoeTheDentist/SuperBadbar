#include "Constants.h"
#include "../util/Analyser.h"
#include "../util/repertories.h"
#include <iostream>
#include "../util/Analyser.h"
#include "../util/macros.h"


/*
*	The 3 next macros will be used to initialize the constants with the value specified in the .h
*	This values should not be used if the constants are defined in the config file
*/
#define LOCAL_INITIALIZE_INT(yop, plop) \
	int Constants::IDENTITY(yop) = plop;
	
#define LOCAL_INITIALIZE_DOUBLE(yop, plop) \
	double Constants::IDENTITY(yop) = plop;
	
#define LOCAL_INITIALIZE_STRING(yop, plop) \
	std::string Constants::IDENTITY(yop) = plop;
	
	
/*
*	The 3 next macros are used to inizialise the constants from the config files
*/	
#define CONST_INIT_INT(yop, plop) \
if (analyser.find_string(QUOTE_ACO(yop))) { \
	 Constants::IDENTITY(yop) = analyser.read_int(); \
}

#define CONST_INIT_DOUBLE(yop, plop) \
if (analyser.find_string(QUOTE_ACO(yop))) { \
	 Constants::IDENTITY(yop) = analyser.read_double(); \
}

#define CONST_INIT_STRING(yop, plop) \
if (analyser.find_string(QUOTE_ACO(yop))) {\
	Constants::IDENTITY(yop) = analyser.read_string(); \
}


FOR_EACH_CONST_INT(LOCAL_INITIALIZE_INT)
FOR_EACH_CONST_DOUBLE(LOCAL_INITIALIZE_DOUBLE)
FOR_EACH_CONST_STRING(LOCAL_INITIALIZE_STRING)

void Constants::init()
{
	Analyser analyser;
	analyser.open(DATA_R + "config.cfg");
	initAux(analyser);
	analyser.close();
	Analyser secondAnalyser;
	if (secondAnalyser.open(DATA_R + "myconfig.cfg")) {
		initAux(secondAnalyser);
		secondAnalyser.close();
	}

}

void Constants::initAux(Analyser &analyser)
{
	FOR_EACH_CONST_INT(CONST_INIT_INT)
	FOR_EACH_CONST_INT(CONST_INIT_DOUBLE)
	FOR_EACH_CONST_STRING(CONST_INIT_STRING)
}

