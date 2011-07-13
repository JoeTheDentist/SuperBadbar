#ifndef _UTIL_CONSTANTS_H_
#define _UTIL_CONSTANTS_H_

#include <string>

/*
*	DEFINE VARIABLES HERE!!
*	The next macros are used to define the variables
*	Enter macro(variableName, variableFakeValue) to add a variable
*	Chose the good type and don't forget to end the macro's line with \
*/
#define FOR_EACH_CONST_INT(macro) \
	macro(FULL_SCREEN, 0) \
	macro(WINDOW_WIDTH, 600) \
	macro(WINDOW_HEIGHT, 800) \
	macro(LAST_LEVEL, 5) 

#define FOR_EACH_CONST_DOUBLE(macro) \
	
	
#define FOR_EACH_CONST_STRING(macro) \
	macro(TEST_LEVEL, "test.lvl")
	
	
/*
*	Macros used to declare variables in the class Constants
*/
	
#define DECLARE_CONST_INT(yop, plop) \
	static int yop;
	
#define DECLARE_CONST_DOUBLE(yop, plop) \
	static double yop;
	
#define DECLARE_CONST_STRING(yop, plop) \
	static std::string yop;


class Analyser;

/*!
*	@class Constants
*	@brief Loads constants from a config file at the begining of the application
*
*	To add variables, go up in this file ;)
*	To access variables, use Constants::variableName
*	To define variables in config files, use this format:
*	{variableName} value
*
*	For strings values, don't specify the quotes (unless you want them to appear in the string)
*
*	The variables can be load from file by calling init()
*	You can reload init in the middle of the execution, but this must be done with care...
*/
class Constants {
public:
	/*!
	* @brief Loads the constants from config.cfg file located in the data path
	*/
	static void init();

	/*
	*	Don't pay attention to that, unless you want to modify the class Constants
	*	These macros declare the variables as public static attributes of Constants
	*	The variables are listed in a macro located at the begining of this file
	*/
	FOR_EACH_CONST_INT(DECLARE_CONST_INT)
	FOR_EACH_CONST_DOUBLE(DECLARE_CONST_DOUBLE)
	FOR_EACH_CONST_STRING(DECLARE_CONST_STRING)
	
protected:
	static void initAux(Analyser &analyser);
};

#endif
